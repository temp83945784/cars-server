#include "Car.h"
#include "Database.h"
#include "Respond.h"
#include <cpp-httplib/httplib.h>

int main(void)
{
    httplib::Server server;
    Database database;

    server.Post("/cars", [&](httplib::Request const& req, httplib::Response& res) {
        auto maybe_car = Car::try_create_from_post_body(req.body);
        if (!maybe_car.has_value()) {
            Respond::error_400(res);
            return;
        }
        if (auto created_car = database.insert_car(maybe_car.value()))
            Respond::status_200(res, created_car.value().as_json_string());
        else
            Respond::error_400(res);
    });

    server.Get(R"(/cars/(\d+))", [&](httplib::Request const& req, httplib::Response& res) {
        auto query_param = req.matches[1];
        if (auto found_car = database.get_car(query_param))
            Respond::status_200(res, found_car.value().as_json_string());
        else
            Respond::error_404(res);
    });

    server.Delete(R"(/cars/(\d+))", [&](httplib::Request const& req, httplib::Response& res) {
        auto query_param = req.matches[1];
        if (auto deleted_car = database.delete_car(query_param))
            Respond::status_203(res, deleted_car.value().as_json_string());
        else
            Respond::error_404(res);
    });

    std::cout << "Server started at localhost:8080\n";
    server.listen("0.0.0.0", 8080);
}
