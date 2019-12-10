#include "Data.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

Data::Data(){
}


Data::~Data(){
	//std::cout << "Object De-allocated";
}

void Data::readData() {

	std::ifstream populationData("..\\Data\\Data.csv");

	if (!populationData.is_open()) {
		std::cout << "Error, file failed to open." << std::endl;
	}
		

	int count{0};
	std::string temp;

	while (getline(populationData, temp)) {
		if (count > 0) {
			std::stringstream S(temp);
			std::string number, city, f_date, s_date, t_date{}; //f_date (first date = 1991)
			getline(S, number, ',');
			getline(S, city, ',');
			getline(S, f_date, ',');
			getline(S, s_date, ',');
			getline(S, t_date, ',');

			if (f_date == "...")
				f_date = "0";

			if (s_date == "...")
				s_date = "0";

			if (t_date == "...")
				t_date = "0";


			//parse number as an int and add it to the vector
			std::stringstream to_Uint(number);
			int temp_num{0};
			to_Uint >> temp_num;

			//parse f_date as an int and add it to the vector
			std::stringstream to_int_1(f_date);
			int temp_fdate{ 0 };
			to_int_1 >> temp_fdate;

			//parse s_date as an int and add it to the vector
			std::stringstream to_int_2(s_date);
			int temp_sdate{ 0 };
			to_int_2 >> temp_sdate;

			//parse t_date as an int and add it to the vector
			std::stringstream to_int_3(t_date);
			int temp_tdate{ 0 };
			to_int_3 >> temp_tdate;

			this->Number.push_back(temp_num);
			this->City.push_back(city);
			this->population_1991.push_back(temp_fdate);
			this->population_2001.push_back(temp_sdate);
			this->population_2011.push_back(temp_tdate);
		}
		count++;
	}
	
	//std::cout << "Population Data Loaded Successfully." << std::endl;
	populationData.close();
}

/*
void Data::determineMinMax(){

	float min_1991{ std::numeric_limits<float>::max() };
	float max_1991{ std::numeric_limits<float>::lowest() };
	float min_2001{ std::numeric_limits<float>::max() };
	float max_2001{ std::numeric_limits<float>::lowest() };
	float min_2011{ std::numeric_limits<float>::max() };
	float max_2011{ std::numeric_limits<float>::lowest() };

	for (int x = 0; x < population_1991.size(); x++) {

		if (static_cast<float>(population_1991.at(x)) > max_1991) {

			max_1991 = static_cast<float>(population_1991.at(x));
		}

		if (static_cast<float>(population_1991.at(x)) < min_1991) {

			if (static_cast<float>(population_1991.at(x)) != 0) {

				min_1991 = static_cast<float>(population_1991.at(x));
			}
		}
	}

	for (int x = 0; x < population_2001.size(); x++) {

		if (static_cast<float>(population_2001.at(x)) > max_2001) {

			max_2001 = static_cast<float>(population_2001.at(x));
		}

		if (static_cast<float>(population_2001.at(x)) < min_2001) {

			if (static_cast<float>(population_2001.at(x)) != 0) {

				min_2001 = static_cast<float>(population_2001.at(x));
			}
		}
	}

	for (int x = 0; x < population_2011.size(); x++) {

		if (static_cast<float>(population_2011.at(x)) > max_2011) {

			max_2011 = static_cast<float>(population_2011.at(x));
		}

		if (static_cast<float>(population_2011.at(x)) < min_2011) {

			if (static_cast<float>(population_2011.at(x)) != 0) {

				min_2011 = static_cast<float>(population_2011.at(x));
			}
		}
	}

	this->min_1991 = min_1991;
	this->max_1991 = max_1991;
	this->min_2001 = min_2001;
	this->max_2001 = max_2001;
	this->min_2011 = min_2011;
	this->max_2011 = max_2011;

} */

void Data::normalisedPopulationData(){
	
	for (int x = 0; x < population_1991.size(); x++) {

		if (population_1991.at(x) != 0) {

			float normalisedData = (population_1991.at(x)) / (max_1991);

			normalised_population_1991.push_back(normalisedData);
		}
		else {
			normalised_population_1991.push_back(0);
		}
	}

	for (int x = 0; x < population_2001.size(); x++) {

		if (population_2001.at(x) != 0) {

			float normalisedData = (population_2001.at(x)) / (max_2001);

			normalised_population_2001.push_back(normalisedData);
		}
		else {
			normalised_population_2001.push_back(0);
		}
	}

	for (int x = 0; x < population_2011.size(); x++) {

		if (population_2011.at(x) != 0) {

			float normalisedData = (population_2011.at(x)) / (max_2011);

			normalised_population_2011.push_back(normalisedData);
		}
		else {
			normalised_population_1991.push_back(0);
		}
	}
	//std::cout << "Population Data Normalised" << std::endl;
}


/*
	I could've saved hundreds of lines of codes  by creating functions to generate the triangles I needed but I opted not to as i thought
	it would help me visualise what i was rendering. In the case that I rendered a triangle with wrong vertices, i could easily see which one 
	was causing the problem.

*/

void Data::showYearPopulationDetails(int year){

	if (year == 1991) {

		std::cout << " -----------------------" << std::endl;
		std::cout << "|City|Population in 1991|" << std::endl;
		std::cout << " -----------------------" << std::endl;

		for (int x = 0; x < population_1991.size(); x++) {

			if(population_1991.at(x) == 0)
				std::cout << "|" << City.at(x) << " - " << "Not Recorded" << std::endl;
			else
				std::cout << "|" << City.at(x) << " - " << population_1991.at(x) << std::endl;

		}

	}

	else if (year == 2001) {

		std::cout << " -----------------------" << std::endl;
		std::cout << "|City|Population in 2001|" << std::endl;
		std::cout << " -----------------------" << std::endl;

		for (int x = 0; x < population_2001.size(); x++) {

			if (population_2001.at(x) == 0)
				std::cout << "|" << City.at(x) << " - " << "Not Recorded" << std::endl;
			else
				std::cout << "|" << City.at(x) << " - " << population_2001.at(x) << std::endl;

		}

	}

	else if (year == 2011) {

		std::cout << " -----------------------" << std::endl;
		std::cout << "|City|Population in 2011|" << std::endl;
		std::cout << " -----------------------" << std::endl;

		for (int x = 0; x < population_2011.size(); x++) {

			if (population_2011.at(x) == 0)
				std::cout << "|" << City.at(x) << " - " << "Not Recorded" << std::endl;
			else
				std::cout << "|" << City.at(x) << " - " << population_2011.at(x) << std::endl;

		}

	}

}

//Turn a coordinate into a points for a 3d rectangle
std::vector<float> Data::toWorldCoordinates(int rawScreenCoordinates[], int dataCount, unsigned int year, unsigned int width, unsigned int height) {

	std::vector<float> normalisedCoordinates;

	const float sideLength = 3.0;
	//const float triangleSide = 5 * sin(45);
	//const float square = 5 * cos(45);

	if (year == 1991) {

		for (int x = 0; x < dataCount; x += 2) {

			//Determine whether x value is in positive or negative region
			if (rawScreenCoordinates[x] > (width / 2)) {

				//Determine whether y value is in positive or negative region
				if (rawScreenCoordinates[x + 1] > (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);
				}

				else if (rawScreenCoordinates[x + 1] <= (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

				}


			}
			
			else if (rawScreenCoordinates[x] <= (width / 2)) {

				if (rawScreenCoordinates[x + 1] <= (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

				}

				else if (rawScreenCoordinates[x + 1] > (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

				}

			}

		}
		
	}

	else if (year == 2001) {

		for (int x = 0; x < dataCount; x += 2) {

			//Determine whether x value is in positive or negative region
			if (rawScreenCoordinates[x] > (width / 2)) {

				//Determine whether y value is in positive or negative region
				if (rawScreenCoordinates[x + 1] > (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);
				}

				else if (rawScreenCoordinates[x + 1] <= (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

				}


			}

			else if (rawScreenCoordinates[x] <= (width / 2)) {

				if (rawScreenCoordinates[x + 1] <= (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

				}

				else if (rawScreenCoordinates[x + 1] > (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

				}

			}

		}

	}

	else if (year == 2011) {

		for (int x = 0; x < dataCount; x += 2) {

			//Determine whether x value is in positive or negative region
			if (rawScreenCoordinates[x] > (width / 2)) {

				//Determine whether y value is in positive or negative region
				if (rawScreenCoordinates[x + 1] > (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);
				}

				else if (rawScreenCoordinates[x + 1] <= (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)));
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

				}


			}

			else if (rawScreenCoordinates[x] <= (width / 2)) {

				if (rawScreenCoordinates[x + 1] <= (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					normalisedCoordinates.push_back(zPos);

				}

				else if (rawScreenCoordinates[x + 1] > (height / 2)) {

					//Top Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Top Right
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

					//Bottom Left
					normalisedCoordinates.push_back((((rawScreenCoordinates[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					normalisedCoordinates.push_back((((rawScreenCoordinates[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					normalisedCoordinates.push_back(zPos);

				}

			}

		}

	}

	else {
		std::cout << "Invalid Year" << std::endl;
	}

	return normalisedCoordinates;
}

std::vector<float> Data::generateSides(int squarePopulation[], int dataCount, unsigned int year, unsigned int width, unsigned int height) {

	std::vector<float> sides;

	const float sideLength = 3.0;
	float adjustedZPos = 0.2;

	if (year == 1991) {

		int i = 0;
		 //Adjusted zpos base on population

		for (int x = 0; x < dataCount; x += 2) {	
			adjustedZPos = normalised_population_1991.at(i);

			/*try {
				adjustedZPos = normalised_population_1991.at(i);
			}
			catch (std::out_of_range) {};*/

			if (squarePopulation[x] > (width / 2)) {

				if (squarePopulation[x + 1] > (height / 2)) {

					//face (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//right (top left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//top (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);
				}

				else if (squarePopulation[x + 1] <= (height / 2)) {
					
					//face (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//right (top left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//top (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

				}

			}
			
			else if (squarePopulation[x] <= (width / 2)) {

				if (squarePopulation[x + 1] > (height / 2)) {

					//face (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//right (top left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//top (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

				}

				else if (squarePopulation[x + 1] <= (height / 2)) {
					
				//face (top left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//face (top right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//face (bottom left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//face bottom right
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//face (top right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//face (bottom left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);





				//left (top left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//left (top right)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//left (bottom left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//left (bottom right)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//left (top right)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//left (bottom left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);





				//right (top left)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//right (top right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//right (bottom left)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//right (bottom right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//right (top right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//right (bottom left)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);





				//top (far left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//top (far right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//top (near left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//top (near right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//top (far right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//top (near left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);





				//bottom (far left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//bottom (far right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//bottom (near left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//bottom (near right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				//bottom (far right)
				sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(zPos);

				//bottom (near left)
				sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
				sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
				sides.push_back(adjustedZPos);

				}

			}
			i++;
		}

	}

	else if (year == 2001) {
		
		int i = 0;

		for (int x = 0; x < dataCount; x += 2) {

			adjustedZPos = normalised_population_2011.at(i);

			if (squarePopulation[x] > (width / 2)) {

				if (squarePopulation[x + 1] > (height / 2)) {

					//face (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//right (top left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//top (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);
				}

				else if (squarePopulation[x + 1] <= (height / 2)) {

					//face (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//right (top left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//top (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

				}

			}

			else if (squarePopulation[x] <= (width / 2)) {

				if (squarePopulation[x + 1] > (height / 2)) {

					//face (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//right (top left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//top (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

				}

				else if (squarePopulation[x + 1] <= (height / 2)) {

					//face (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//right (top left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//top (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

				}

			}
			i++;
		}
		
	}

	else if (year == 2011) {

	int i = 0;
		
		for (int x = 0; x < dataCount; x += 2) {

			adjustedZPos = normalised_population_1991.at(i);

			if (squarePopulation[x] > (width / 2)) {

				if (squarePopulation[x + 1] > (height / 2)) {

					//face (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//right (top left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//top (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);
				}

				else if (squarePopulation[x + 1] <= (height / 2)) {

					//face (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//right (top left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//top (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back(((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back(((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2));
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

				}

			}

			else if (squarePopulation[x] <= (width / 2)) {

				if (squarePopulation[x + 1] > (height / 2)) {

					//face (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//right (top left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);





					//top (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)) * -1);
					sides.push_back(adjustedZPos);

				}

				else if (squarePopulation[x + 1] <= (height / 2)) {

					//face (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face bottom right
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//face (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//left (top left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//left (bottom right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (top right)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//left (bottom left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//right (top left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//right (bottom right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (top right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//right (bottom left)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);





					//top (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//top (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//top (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] + sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);





					//bottom (far left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (near right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

					//bottom (far right)
					sides.push_back((((squarePopulation[x] + sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(zPos);

					//bottom (near left)
					sides.push_back((((squarePopulation[x] - sideLength) - (width / 2)) / (width / 2)) * -1);
					sides.push_back((((squarePopulation[x + 1] - sideLength) - (height / 2)) / (height / 2)));
					sides.push_back(adjustedZPos);

				}

			}
			i++;
		}

	}

	return sides;
}



