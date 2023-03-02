import http from 'k6/http';
import { check } from 'k6';

const API_URL = 'http://localhost:8080';

const createCar = (car) => {
  const payload = JSON.stringify(car);
  const headers = { 'Content-Type': 'application/json' };
  return http.post(`${API_URL}/cars`, payload, { headers });
}

const getCar = (carId) => {
  return http.get(`${API_URL}/cars/${carId}`);
}

const deleteCar = (carId) => {
  return http.del(`${API_URL}/cars/${carId}`);
}

export default function () {
  const car = {
    brand: 'ford',
    model: 'f150',
    horse_power: '200',
  };

  // Create car
  let res = createCar(car);
  check(res, {
    'status was 200': (r) => r.status == 200,
    "brand is ok": (r) => r.json()["brand"] === car.brand,
    "model is ok": (r) => r.json()["model"] === car.model,
    "horse_power is ok": (r) => r.json()["horse_power"] === car.horse_power,
    "id is ok": (r) => r.json()["id"] !== undefined,
  });
  let createdCarId = res.json()["id"];

  // Get car by id
  res = getCar(createdCarId);
  check(res, {
    'status was 200': (r) => r.status == 200,
  });

  // Delete car by id
  res = deleteCar(createdCarId);
  check(res, {
    'status was 203': (r) => r.status == 203,
  });
}