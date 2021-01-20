#ifndef APRS_POSITION_H_
#define APRS_POSITION_H_

#include "APRSMessage.h"

enum class APRSPositionTypes
{
	Message,			// =
	MessageTimestamp,	// @
	Timestamp,			// /
	Nothing,			// !
};

enum class Symbol
{
	Car
};

class APRSPosition : public APRSBody
{
public:
	APRSPosition();
	virtual ~APRSPosition();

	Symbol getSymbol() const;
	void setSymbol(const Symbol symbol);
	
	double getLatitude() const;
	void setLatitude(const double lat);

	double getLongitude() const;
	void setLongitude(const double longi);

	int getTime() const;
	void setTime(const int time);

	String getMessage() const;
	void setMessage(const String & message);

	APRSPositionTypes getPositionType() const;

	virtual bool decode(const String & message);
	virtual String encode() const;
	virtual String toString() const;

private:
	Symbol _symbol;
	double _lat;
	double _long;
	int _time;
	bool _timeIsSet;
	String _message;
	bool _messageIsSet;

	APRSPositionTypes decodePositionType(const String & message);
	char encodePositionType();
};

#endif
