#pragma once

#include <nlohmann/json.hpp>
#include <optional>

class Car {
public:
    Car(int id, std::string brand, std::string model, std::string horse_power);

    static std::optional<Car> try_create_from_post_body(std::string const& stringified_car);

    std::string as_json_string();

    std::string brand() const { return m_brand; }
    std::string model() const { return m_model; }
    std::string horse_power() const { return m_horse_power; }

private:
    Car(nlohmann::json const& car);

    static bool is_valid_car(nlohmann::json const& car);

    int m_id = -1;
    std::string m_brand;
    std::string m_model;
    std::string m_horse_power;
};
