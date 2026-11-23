#pragma once
#include <string>

namespace paperos {
// Restrict all requests, including credential-bearing ones, to TLS.
inline bool isSecureUrl(const std::string& url) {
    return url.compare(0, 8, "https://") == 0 && url.size() > 8;
}
inline bool hasPemCertificate(const std::string& pem) {
    const auto begin = pem.find("-----BEGIN CERTIFICATE-----");
    return begin != std::string::npos &&
           pem.find("-----END CERTIFICATE-----", begin + 27) != std::string::npos;
}
}
