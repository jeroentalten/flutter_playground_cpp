#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "httplib.h"

#define SERVER_URL "https://chat.tissink.me"

const std::string SECURITY_TOKEN = "WcRa962TFQ5MgFja3enssESn7SBMKvkaVr2JrdvwJEKEJanD5RKU36JC8ejK";

httplib::Headers headers = {
    { "Authorization", SECURITY_TOKEN }
};

// Base64 encoding function
std::string base64_encode(const std::vector<unsigned char>& data) {
    static const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string encoded;
    int val = 0, valb = -6;
    for (unsigned char c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            encoded.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) encoded.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (encoded.size() % 4) encoded.push_back('=');
    return encoded;
}

// Function to read a file into a byte vector
std::vector<unsigned char> read_file_as_bytes(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return {};
    return std::vector<unsigned char>(std::istreambuf_iterator<char>(file), {});
}

extern "C" {

// Function to send a text message with a username
const char* send_message(const char* username, const char* message) {
    static std::string response;
    response.clear();

    httplib::Client cli(SERVER_URL);
    httplib::Params params;
    params.emplace("username", username);
    params.emplace("message", message);

    auto res = cli.Post("/message", params);

    if (res) {
        response = res->body;
    } else {
        response = "Error: Failed to send request";
    }

    return response.c_str();
}

// Function to send an image (Base64 encoded) with a username
const char* send_image(const char* username, const char* image_path) {
    static std::string response;
    response.clear();

    // Read file and encode to Base64
    auto image_data = read_file_as_bytes(image_path);
    if (image_data.empty()) {
        response = "Error: Failed to read image file";
        return response.c_str();
    }
    std::string base64_image = base64_encode(image_data);

    httplib::Client cli(SERVER_URL);
    httplib::Params params;
    params.emplace("username", username);
    params.emplace("image", base64_image);  // Send Base64 string

    auto res = cli.Post("/message", params);

    if (res) {
        response = res->body;
    } else {
        response = "Error: Failed to send image";
    }

    return response.c_str();
}

}
