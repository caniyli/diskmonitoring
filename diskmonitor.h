#ifndef DISKMONITOR_H
#define DISKMONITOR_H

#include "monitoring.grpc.pb.h"
#include <QObject>
#include <google/protobuf/empty.pb.h>
#include <grpc++/grpc++.h>

using mon::DiskMonitoring;

class DiskMonitor : public QObject
{
	Q_OBJECT
public:
	DiskMonitor(const std::string &ep);
	~DiskMonitor();
	mon::AllDiskResponse GetBPS();
	mon::DiskResponse GetDiskBPS(std::string name);
	mon::AllDiskResponse GetIOPS();
	mon::DiskResponse GetDiskIOPS(std::string name);
	mon::AllDiskResponse GetRequestSizeInBytesPerRead();
	mon::DiskResponse GetDiskRequestSizeInBytesPerRead(std::string name);

private:
	void CreateChannel(const std::string &ep);
	std::unique_ptr<DiskMonitoring::Stub> stub = nullptr;
	std::string endpoint;
};

#endif // DISKMONITOR_H
