# API REST C++ 🚗

Servidor hecho en C++ para crear, consultar y gestionar coches.

Desarrollado por Martin Falisse.

## Prerrequisitos

Instalar Docker para poder lanzar el servidor: https://docs.docker.com/engine/install/ubuntu/

Instalar k6 para poder lanzar los tests: https://k6.io/docs/get-started/installation/

## Cómo ejecutar el servicio

1. Clonar este repositorio
1. Ejecutar `docker compose up` en la raíz de este directorio

## Cómo ejecutar la prueba k6.io

1. Lanzar el servidor tal como indicado arriba
2. Ejecutar `k6 run test.js` en la carpeta `k6-tests/`
