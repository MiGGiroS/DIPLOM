#include "stdafx.h"
#pragma once

#include <ctime>


// типы данных
#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int

// выравнивание структур на 1 байт
#pragma pack(push,1)

struct BlockInfo
{
    int offset;
    double ver;
    DWORD size;
    char *data;
};

struct EventEntry
{
    int unajustedDistance; // N x 0.1ns
    double distance;
    double slope;
    double spliceLoss;
    double reflectionLoss;
    char * eventType;
    char * comment;
    System::String^ strType();
    System::String^ strComment();
};

class OTDR
{
public:
    char* filename;
    struct BlockInfo map;
    struct BlockInfo gen;
    struct BlockInfo fxd;
    struct BlockInfo sup;
    struct BlockInfo pnt;
    struct BlockInfo evt;

    // General Parameters Block
    char * cableID;
    char * fiberID;
    int fiberType;
    int wavelength;
    char * locationA;
    char * locationB;
    char * cableCode;
    char * buildCondition; // 2xBYTE
    char * Operator;
    char * comments;

    // Supplier Parameters Block
    char * supplierName;
    char * OTDRName;
    char * OTDRSerialNumber;
    char * moduleName;
    char * moduleSerialNumber;
    char * softwareVersion;
    char * supOther;

    // Fixed parameters
    time_t time; // unixtime
    int units; // возможные варианты - km, mt, ft, kf, mi
    double fxdWavelength;
    int acqOffset;
    int acqOffsetDistance;
    int numPulseWidthEntries;
    int pulsewidth; // ns
    double sampleSpacing;
    int dpntCnt;
    double indexOfRefraction;
    double backscatteringCoefficient; // dB
    int numberOfAvg;
    double avgTime;
    double range; // km (x2)
    int acqRangeDistance;
    int frontPanelOfst;
    int noiseFloorLevel;
    int noiseFloorScaling;
    int powerOffsetFP;
    double lossThreshold; // dB
    double reflectionThreshold; // dB
    double EOTThreshold; // dB
    int TraceType; // варианты - ST, RT, DR, RF
    int X1, Y1, X2, Y2;
    double adjResolution;
    double adjRange;

    // Data points
    int numDataPoints;
    int numOfTraces;
    double scalingFactor;
    WORD* dataPoints;
    double pntMax, pntMin;

    // Events
    int eventCount;
    struct EventEntry *events;

public:
    OTDR(char* filename);
    ~OTDR();
    void parseGenParams();
    void parseSupParams();
    void parseFxdParams();
    void parseKeyEvents();
    void parseDataPts();

    System::String^ shortFilename();
    System::String^ strUnit();
    System::String^ strFiberType();
    System::String^ strBuildCondition();
    System::String^ strTraceType();
};
