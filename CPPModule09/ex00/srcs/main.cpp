/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:09:41 by schuah            #+#    #+#             */
/*   Updated: 2023/08/16 21:52:36 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <map>

#define DATA_FILE std::string("srcs/data.csv")

struct Date
{
	Date() : year(-1), month(-1), day(-1) {}
	int year;
	int month;
	int day;
};

void errorExit(std::string msg)
{
	std::cout << msg << std::endl;
	exit(EXIT_FAILURE);
}

int dateIsValid(int year, int month, int day)
{
	std::array<int, 12> maxDay = {31, 28 + (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	return ((year >= 1 && month >= 1 && month <= 12 && day >= 1 && day <= maxDay[month - 1]));
}

double getData(std::map<std::string, double> data, std::string date)
{
	std::map<std::string, double>::iterator it = data.find(date);
	return (it == data.end() ? std::prev(data.lower_bound(date))->second : it->second);
}

Date parseDate(const std::string &dateString)
{
	Date date;
	std::istringstream iss(dateString);
	char delimiter;
	iss >> date.year >> delimiter >> date.month >> delimiter >> date.day;
	return date;
}

std::string checkDateFormat(std::string line, std::string date, bool input)
{
	static Date startDate;

	if (date.length() != 10)
		return ("Error: invalid date format: " + line);
	for (size_t i = 0; i < date.length(); i++)
	{
		if ((i == 4 || i == 7) && date[i] != '-')
			return ("Error: invalid date format: " + line);
		else if ((i != 4 && i != 7) && (date[i] < '0' || date[i] > '9'))
			return ("Error: invalid date format: " + line);
	}

	if (startDate.year == -1 && startDate.month == -1 && startDate.day == -1)
		startDate = parseDate(line.substr(0, 10));

	Date currentDate = parseDate(line.substr(0, 10));

	if (input == true && (startDate.year > currentDate.year ||
												(startDate.year == currentDate.year && startDate.month > currentDate.month) ||
												(startDate.year == currentDate.year && startDate.month == currentDate.month && startDate.day > currentDate.day)))
		return "Error: invalid date: " + line;

	return ((dateIsValid(std::atoi(date.substr(0, 4).c_str()), std::atoi(date.substr(5, 2).c_str()), std::atoi(date.substr(8, 2).c_str())) == false) ? "Error: invalid date: " + line : "");
}

std::string checkValueFormat(std::string line, std::string number, int data = 1)
{
	if (number.find('.') != number.find_last_of('.') || number.length() == 0)
		return ("Error: invalid exchange rate value: " + line);
	for (size_t i = 0; i < number.length(); i++)
	{
		if ((number[i] < '0' || number[i] > '9') && number[i] != '.')
			return ("Error: invalid exchange rate value: " + line);
	}
	if (data == 0 && (std::stod(number) < 0 || std::stod(number) > 1000))
		return ("Error: invalid value: " + line);
	return ("");
}

std::map<std::string, double> parseData()
{
	std::ifstream dataFile(DATA_FILE);
	std::map<std::string, double> output;
	std::string line;

	if (dataFile.is_open() == false)
		errorExit("Error: could not open data file: " + DATA_FILE);
	std::getline(dataFile, line);
	if (line != "date,exchange_rate")
		errorExit("Error: invalid data file format: " + line);
	while (std::getline(dataFile, line))
	{
		std::string date = line.substr(0, line.find(','));
		std::string error = checkDateFormat(line, date, false);
		if (error.empty() == false)
			errorExit(error);
		std::string exchangeRate = line.substr(line.find(',') + 1);
		error = checkValueFormat(line, exchangeRate);
		if (error.empty() == false)
			errorExit(error);
		output[date] = std::stod(exchangeRate);
	}
	dataFile.close();
	return (output);
}

void parseInput(std::map<std::string, double> data, std::string path)
{
	std::ifstream inputFile(path);
	std::string line;
	if (inputFile.is_open() == false)
		errorExit("could not open input file: " + path);
	std::getline(inputFile, line);
	if (line != "date | value")
		errorExit("invalid input file format: " + line);
	while (std::getline(inputFile, line))
	{
		std::string date = line.substr(0, line.find('|') - 1);
		std::string error = checkDateFormat(line, date, true);
		if (error.empty() == false)
		{
			std::cout << error << std::endl;
			continue;
		}
		std::string value = line.substr(line.find('|') + 2);
		error = checkValueFormat(line, value, 0);
		if (error.empty() == false)
		{
			std::cout << error << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << getData(data, date) * std::stod(value) << std::endl;
	}
	(void)data;
}

int main(int ac, char **av)
{
	if (ac != 2)
		errorExit("invalid number of arguments");
	std::map<std::string, double> data = parseData();
	parseInput(data, std::string(av[1]));
	return (0);
}
