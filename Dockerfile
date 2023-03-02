FROM ubuntu:22.04

RUN apt-get -y update
RUN apt-get -y install build-essential mariadb-server wget

# Get C++ dependencies
WORKDIR /usr/downloads/
RUN wget -O mariadb-connector-cpp-1.0.2-ubuntu-jammy-amd64.tar.gz https://dlm.mariadb.com/2531516/Connectors/cpp/connector-cpp-1.0.2/mariadb-connector-cpp-1.0.2-ubuntu-jammy-amd64.tar.gz
RUN tar -xf mariadb-connector-cpp-1.0.2-ubuntu-jammy-amd64.tar.gz 
RUN mv ./mariadb-connector-cpp-1.0.2-ubuntu-jammy-amd64/include/mariadb/ /usr/include/mariadb/
RUN mv ./mariadb-connector-cpp-1.0.2-ubuntu-jammy-amd64/lib/mariadb/libmariadbcpp.so /usr/lib/
RUN mv ./mariadb-connector-cpp-1.0.2-ubuntu-jammy-amd64/lib/mariadb/ /usr/lib/mariadb/

RUN wget -O cpp-httplib-0.12.0.tar.gz https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.12.0.tar.gz
RUN tar -xf cpp-httplib-0.12.0.tar.gz 
RUN mv ./cpp-httplib-0.12.0/ /usr/include/cpp-httplib/

RUN wget -O json-3.11.2.tar.gz https://github.com/nlohmann/json/archive/refs/tags/v3.11.2.tar.gz
RUN tar -xf json-3.11.2.tar.gz 
RUN mv ./json-3.11.2/single_include/nlohmann/ /usr/include/nlohmann/

WORKDIR /usr/
RUN rm -rf /usr/downloads/

# Get source code
COPY ./src/ /usr/app/

# Compile
WORKDIR /usr/app/
RUN g++ main.cpp Car.cpp Database.cpp -lmariadbcpp -o main -O2

# Run
CMD ["./main"]