#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include "lookup.hpp"

constexpr int PORT = 80;
constexpr int BUFFER_SIZE = 4096;

std::string http_response(int status_code, const std::string& content, const std::string& content_type = "application/json") {
    return 
        "HTTP/1.1 " + std::to_string(status_code) + " OK\r\n"
        "Content-Type: " + content_type + "\r\n"
        "Content-Length: " + std::to_string(content.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" + content;
}

int main() {
    LibBIN::Lookup::load_bins();

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    std::cout << "Server running on port " << PORT << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        char buffer[BUFFER_SIZE]{};
        ssize_t read_bytes = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (read_bytes < 0) {
            perror("read");
            close(client_fd);
            continue;
        }

        std::string request(buffer, read_bytes);
        std::cout << "Received request:\n" << request << "\n";

        const std::string prefix = "GET /lookup/";
        size_t pos = request.find(prefix);
        std::string response_body;

        if (pos != std::string::npos) {
            size_t start = pos + prefix.size();
            size_t end = request.find(' ', start);
            std::string bin = request.substr(start, end - start);

            auto result = LibBIN::Lookup::Search(bin);
            if (result) {
                response_body = "{";
                response_body += "\"success\":true,";
                response_body += "\"bin\":\"" + result->bin + "\",";
                response_body += "\"scheme\":\"" + result->scheme + "\",";
                response_body += "\"type\":\"" + result->type + "\",";
                response_body += "\"brand\":\"" + result->brand + "\",";
                response_body += "\"bank\":\"" + result->bank + "\",";
                response_body += "\"country\":\"" + result->country + "\",";
                response_body += "\"country_code\":\"" + result->country_code + "\",";
                response_body += "\"level\":\"" + result->level + "\",";
                response_body += "\"country_flag\":\"" + result->country_flag + "\",";
                response_body += "\"prepaid\":" + std::string(result->prepaid ? "true" : "false") + ",";
                response_body += "\"is_valid\":" + std::string(result->is_valid ? "true" : "false");
                response_body += "}";
                std::string response = http_response(200, response_body);
                write(client_fd, response.c_str(), response.size());
            } else {
                response_body = "{\"success\":false,\"error\":\"" + std::string(result.error().what()) + "\"}";
                std::string response = http_response(404, response_body);
                write(client_fd, response.c_str(), response.size());
            }
        } else {
            std::string response = http_response(400, "{\"success\":false,\"error\":\"Bad request\"}");
            write(client_fd, response.c_str(), response.size());
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
