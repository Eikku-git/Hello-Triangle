#include "iostream"
#include "app.hpp"

int main() {
	app_data data = app_data();
	init(data);
	run(data);
	terminate(data);
	return 0;
}