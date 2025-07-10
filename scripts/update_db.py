import os
import requests

BIN_DB_URL = "https://raw.githubusercontent.com/Junaid433/LibBIN/main/data/bin_data.csv"
default_path = "/usr/share/bin_lookup/bin_data.csv"
local_path = os.path.join(os.path.dirname(__file__), "..", "data", "bin_data.csv")
OUTPUT_PATH = default_path if os.path.exists(default_path) else local_path

def download_bin_db(url: str, output_path: str):
    print(f"Downloading BIN DB from {url}...")
    try:
        response = requests.get(url, timeout=30)
        response.raise_for_status()
    except Exception as e:
        print(f"Failed to download BIN DB: {e}")
        return False

    os.makedirs(os.path.dirname(output_path), exist_ok=True)

    if os.path.exists(output_path):
        os.remove(output_path)

    with open(output_path, "wb") as f:
        f.write(response.content)
    print(f"BIN DB saved to {output_path}")
    return True

if __name__ == "__main__":
    success = download_bin_db(BIN_DB_URL, OUTPUT_PATH)
    if not success:
        exit(1)