#pragma once

#include <cpp-httplib/httplib.h>

struct Respond {
    static void status_200(httplib::Response& res, std::string body)
    {
        res.set_content(body, "application/json");
        res.status = 200;
    }

    static void status_203(httplib::Response& res, std::string body)
    {
        res.set_content(body, "application/json");
        res.status = 203;
    }

    static void error_400(httplib::Response& res)
    {
        res.status = 400;
    }

    static void error_404(httplib::Response& res)
    {
        res.status = 404;
    }
};
