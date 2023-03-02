#include "Car.h"

Car::Car(int id, std::string brand, std::string model, std::string horse_power)
    : m_id(id)
    , m_brand(brand)
    , m_model(model)
    , m_horse_power(horse_power)
{
}

Car::Car(nlohmann::json const& car)
    : m_brand(car["brand"])
    , m_model(car["model"])
    , m_horse_power(car["horse_power"])
{
}

std::string Car::as_json_string()
{
    nlohmann::json json_car = {
        { "id", std::to_string(m_id) },
        { "brand", m_brand },
        { "model", m_model },
        { "horse_power", m_horse_power },
    };
    return json_car.dump();
}

bool Car::is_valid_car(nlohmann::json const& json_car)
{
    if (!json_car["brand"].is_string() || !json_car["model"].is_string() || !json_car["horse_power"].is_string())
        return false;
    // Database uses varchar(200) for storing these values
    if (json_car["brand"].size() > 200 || json_car["model"].size() > 200 || json_car["horse_power"].size() > 200)
        return false;
    return true;
}

std::optional<Car> Car::try_create_from_post_body(std::string const& stringified_car)
{
    // If it's invalid JSON don't continue
    if (!nlohmann::json::accept(stringified_car))
        return {};

    auto json_car = nlohmann::json::parse(stringified_car);
    if (is_valid_car(json_car))
        return Car(json_car);
    return {};
}