#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#define SERVER_URL "https://chat.tissink.me"

const std::string TOKEN_HEADER = "key";
const std::string SECURITY_TOKEN = "WcRa962TFQ5MgFja3enssESn7SBMKvkaVr2JrdvwJEKEJanD5RKU36JC8ejK";

httplib::Client cli(SERVER_URL);
httplib::Headers headers = {
    { TOKEN_HEADER, SECURITY_TOKEN }
};

extern "C" {

// Function to send a text message with a username
const char* send_message(const char* username, const char* message, const char* encodedImage = "") {
    static std::string response;
    response.clear();

    httplib::MultipartFormDataItems items = {
        { "username", username, "", "text/plain" },
        { "message", message, "", "text/plain" },
        { "image", encodedImage, "", "text/plain" }
    };

    auto res = cli.Post("/message", headers, items);

    if (res) {
        response = res->body;
    } else {
        response = "Error: Failed to send request";
    }

    return response.c_str();
}

const char* get_messages() {
    auto res = cli.Get("/messages", headers);

    if (res && res->status == 200) {
        return strdup(res->body.c_str());
    } else {
        return strdup("Error retrieving messages");
    }
}

}

int main() {
    const char* username = "Dennis";
    const char* message = "Heehoi!";
    const char* encodedImage = "<script>alert(\"You've been p0wn3d.\")</script>";

    const char* message_response = send_message(username, message, encodedImage);
    std::cout << "Message Response: " << message_response << std::endl;

    const char* response = get_messages();
    std::cout << "Messages: " << response << std::endl;

    return 0;
}
