#pragma once
#include <array>
#include <iomanip>
#include <sstream>
#include "ur_modern_driver/ur/stream.h"

class URCommander
{
private:
  URStream &stream_;
  URStream stream_dashboard_;

protected:
  bool write(const std::string &s);
  void formatArray(std::ostringstream &out, std::array<double, 6> &values);

public:
  URCommander(URStream &stream) : stream_(stream), stream_dashboard_(stream.host_, 29999)
  {
//    URStream stream_new = URStream(stream.host_, 29999);
  }

  virtual bool speedj(std::array<double, 6> &speeds, double acceleration) = 0;
  virtual bool setDigitalOut(uint8_t pin, bool value) = 0;
  virtual bool setAnalogOut(uint8_t pin, double value) = 0;

  // shared
  bool uploadProg(const std::string &s);
  bool stopj(double a = 10.0);
  bool setToolVoltage(uint8_t voltage);
  bool setFlag(uint8_t pin, bool value);
  bool setPayload(double value);
  bool sendDashboardCmd(const std::string &s);

};

class URCommander_V1_X : public URCommander
{
public:
  URCommander_V1_X(URStream &stream) : URCommander(stream)
  {
  }

  virtual bool speedj(std::array<double, 6> &speeds, double acceleration);
  virtual bool setDigitalOut(uint8_t pin, bool value);
  virtual bool setAnalogOut(uint8_t pin, double value);
};

class URCommander_V3_X : public URCommander
{
public:
  URCommander_V3_X(URStream &stream) : URCommander(stream)
  {
  }

  virtual bool speedj(std::array<double, 6> &speeds, double acceleration) = 0;
  virtual bool setDigitalOut(uint8_t pin, bool value);
  virtual bool setAnalogOut(uint8_t pin, double value);
};

class URCommander_V3_1__2 : public URCommander_V3_X
{
public:
  URCommander_V3_1__2(URStream &stream) : URCommander_V3_X(stream)
  {
  }

  virtual bool speedj(std::array<double, 6> &speeds, double acceleration);
};

class URCommander_V3_3 : public URCommander_V3_X
{
public:
  URCommander_V3_3(URStream &stream) : URCommander_V3_X(stream)
  {
  }

  virtual bool speedj(std::array<double, 6> &speeds, double acceleration);
};
