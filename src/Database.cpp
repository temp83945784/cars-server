#include "Database.h"

#include <iostream>

Database::Database()
{
    sql::Driver* driver = sql::mariadb::get_driver_instance();
    sql::SQLString url("jdbc:mariadb://mariadb:3306/cars");
    sql::Properties properties({ { "user", "admin" }, { "password", "password" } });
    m_connection = driver->connect(url, properties);
}

std::optional<sql::ResultSet*> Database::execute_statement(std::unique_ptr<sql::PreparedStatement> const& statement)
{
    try {
        return statement->executeQuery();
    } catch (sql::SQLException& e) {
        std::cerr << "Error executing statement: " << e.what() << std::endl;
        return {};
    }
}

std::unique_ptr<sql::PreparedStatement> Database::prepare_statement(std::string const& sql_statement, std::string const& id)
{
    std::unique_ptr<sql::PreparedStatement> stmnt(m_connection->prepareStatement(sql_statement));
    stmnt->setString(1, id);
    return stmnt;
}

std::unique_ptr<sql::PreparedStatement> Database::prepare_statement(std::string const& sql_statement, Car const& car)
{
    std::unique_ptr<sql::PreparedStatement> stmnt(m_connection->prepareStatement(sql_statement));
    stmnt->setString(1, car.brand());
    stmnt->setString(2, car.model());
    stmnt->setString(3, car.horse_power());
    return stmnt;
}

std::optional<Car> Database::get_first_car_from_results(sql::ResultSet* result_set)
{
    try {
        result_set->next();
        return Car(result_set->getInt(1),
            std::string(result_set->getString(2)),
            std::string(result_set->getString(3)),
            std::string(result_set->getString(4)));
    } catch (sql::SQLException& e) {
        // No results
        return {};
    }
}

std::optional<Car> Database::insert_car(Car const& car)
{
    auto insert_query = "INSERT INTO cars (brand, model, horse_power) VALUES (?, ?, ?) RETURNING id, brand, model, horse_power;";
    auto statement = prepare_statement(insert_query, car);
    if (auto result = execute_statement(statement))
        return get_first_car_from_results(result.value());
    return {};
}

std::optional<Car> Database::get_car(std::string const& id)
{
    auto select_query = "SELECT id, brand, model, horse_power FROM cars WHERE id = ?;";
    auto statement = prepare_statement(select_query, id);
    if (auto result = execute_statement(statement))
        return get_first_car_from_results(result.value());
    return {};
}

std::optional<Car> Database::delete_car(std::string const& id)
{
    auto delete_query = "DELETE FROM cars WHERE id = ? RETURNING id, brand, model, horse_power;";
    auto statement = prepare_statement(delete_query, id);
    if (auto result = execute_statement(statement))
        return get_first_car_from_results(result.value());
    return {};
}
