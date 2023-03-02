#pragma once

#include "Car.h"
#include <mariadb/conncpp.hpp>
#include <optional>

class Database {
public:
    Database();

    std::optional<Car> insert_car(Car const&);
    std::optional<Car> get_car(std::string const& id);
    std::optional<Car> delete_car(std::string const& id);

private:
    std::optional<sql::ResultSet*> execute_statement(std::unique_ptr<sql::PreparedStatement> const&);

    std::unique_ptr<sql::PreparedStatement> prepare_statement(std::string const& sql_statement, std::string const& id);
    std::unique_ptr<sql::PreparedStatement> prepare_statement(std::string const& sql_statement, Car const&);

    std::optional<Car> get_first_car_from_results(sql::ResultSet*);

    sql::Connection* m_connection;
};
