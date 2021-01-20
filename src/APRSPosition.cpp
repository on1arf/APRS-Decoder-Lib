#include "APRSPosition.h"

APRSPosition::APRSPosition()
{
}

APRSPosition::~APRSPosition()
{
}

Symbol APRSPosition::getSymbol() const
{
	return _symbol;
}

void APRSPosition::setSymbol(const Symbol symbol)
{
	_symbol = symbol;
}

double APRSPosition::getLatitude() const
{
	return _lat;
}

void APRSPosition::setLatitude(const double lat)
{
	_lat = lat;
}

double APRSPosition::getLongitude() const
{
	return _long;
}

void APRSPosition::setLongitude(const double longi)
{
	_long = longi;
}

int APRSPosition::getTime() const
{
	return _time;
}

void APRSPosition::setTime(const int time)
{
	_time = time;
}

String APRSPosition::getMessage() const
{
	return _message;
}

void APRSPosition::setMessage(const String & message)
{
	_message = message;
}

APRSPositionTypes APRSPosition::getPositionType() const
{
	if(_timeIsSet && _messageIsSet)
	{
		return APRSPositionTypes::MessageTimestamp;
	}
	if(_timeIsSet)
	{
		return APRSPositionTypes::Timestamp;
	}
	if(_messageIsSet)
	{
		return APRSPositionTypes::Message;
	}
	return APRSPositionTypes::Nothing;
}

bool APRSPosition::decode(const String & message)
{
	APRSPositionTypes type = decodePositionType(message);
	if(type == APRSPositionTypes::Message)
	{
		// =1234.12N/12345.12E-QTH von AB1CDE
		String lat = message.substring(1, 7);
		char ns = message[8];
		String lng = message.substring(10, 17);
		char ow = message[18];
		// _symbol = message[9] + message[19]
	}
	if(type == APRSPositionTypes::MessageTimestamp)
	{
		// @101733z1234.12N/12345.12E_247/000g002t043r002p002P...h83b10191WX - Linz - Nord
		String lat = message.substring(1+7, 7+7);
		char ns = message[8+7];
		String lng = message.substring(10+7, 17+7);
		char ow = message[18+7];
		// _symbol = message[9+7] + message[19+7]
	}
	return true;
}

String APRSPosition::encode() const
{
	return String();
}

String APRSPosition::toString() const
{
	String s = String("Position: Latitude: ") + _lat + ", Longitude: " + _long;
	if(_timeIsSet)
	{
		s += ", Time: " + _time;
	}
	if(_messageIsSet)
	{
		s += ", Message: " + _message;
	}
	return s;
}

APRSPositionTypes APRSPosition::decodePositionType(const String & message)
{
	switch(message[0])
	{
	case '=':
		return APRSPositionTypes::Message;
	case '@':
		return APRSPositionTypes::MessageTimestamp;
	case '/':
		return APRSPositionTypes::Timestamp;
	case '!':
	default:
		return APRSPositionTypes::Nothing;
	}
}

char APRSPosition::encodePositionType()
{
	switch(getPositionType())
	{
	case APRSPositionTypes::Message:
		return '=';
	case APRSPositionTypes::MessageTimestamp:
		return '@';
	case APRSPositionTypes::Timestamp:
		return '/';
	case APRSPositionTypes::Nothing:
	default:
		return '!';
	}
}
