#pragma once

#include <string>
#include <vector>

class Data{
private:
	const float zPos = 0.00001;
	std::vector<unsigned int> Number;
	std::vector<std::string> City;

	std::vector<int> population_1991;
	std::vector<int> population_2001;
	std::vector<int> population_2011;

	const float min_1991{ 81228.0 };
	const float max_1991{ 6715769.0};
	const float min_2001{ 92415.0 };
	const float max_2001{ 7208384.0 };
	const float min_2011{ 100153.0 };
	const float max_2011{ 8250205.0 };

	std::vector<float> normalised_population_1991;
	std::vector<float> normalised_population_2001;
	std::vector<float> normalised_population_2011;

public:
	Data();
	~Data();
	void readData();
//	void determineMinMax();
	void normalisedPopulationData();
	int getNumber(int index) { return Number.at(index); };
	std::string getCity(int index) { return City.at(index); };
	void showYearPopulationDetails(const int year);
	std::vector<float> toWorldCoordinates(int rawScreenCoordinate[], const int dataCount, const unsigned int year, const unsigned int width, const unsigned int height);
	std::vector<float> generateSides(int rawScreenCoordinate[], const int dataCount, const unsigned int year, const unsigned int width, const unsigned int height);
};

