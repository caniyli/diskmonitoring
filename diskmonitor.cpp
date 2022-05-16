#include "diskmonitor.h"
#include <QDebug>

DiskMonitor::DiskMonitor(const std::string &ep)
{
	endpoint = ep;
	CreateChannel(endpoint);
}

DiskMonitor::~DiskMonitor()
{
}

mon::AllDiskResponse DiskMonitor::GetBPS()
{
	google::protobuf::Empty empty;
	grpc::ClientContext context;
	grpc::Status statusDisks;
	mon::AllDiskResponse diskResponse;
	if (!stub)
		return diskResponse;
	statusDisks = stub->GetBPS(&context, empty, &diskResponse);

	return diskResponse;
}

mon::DiskResponse DiskMonitor::GetDiskBPS(std::string name)
{
	grpc::Status statusStats;
	mon::DiskResponse diskStatsResp;
	mon::DiskResponse diskStatsCtrl;
	mon::DiskQ disk;
	grpc::ClientContext contextDiskStats;
	*disk.mutable_name() = name;
	statusStats = stub->GetDiskBPS(&contextDiskStats, disk, &diskStatsResp);
	if (!stub)
		return diskStatsCtrl;
	return diskStatsResp;
}

mon::AllDiskResponse DiskMonitor::GetIOPS()
{
	google::protobuf::Empty empty;
	grpc::ClientContext context;
	grpc::Status statusDisks;
	mon::AllDiskResponse diskResponse;
	if (!stub)
		return diskResponse;
	statusDisks = stub->GetIOPS(&context, empty, &diskResponse);

	return diskResponse;
}

mon::DiskResponse DiskMonitor::GetDiskIOPS(std::string name)
{
	grpc::Status statusStats;
	mon::DiskResponse diskStatsResp;
	mon::DiskResponse diskStatsCtrl;
	mon::DiskQ disk;
	grpc::ClientContext contextDiskStats;
	*disk.mutable_name() = name;
	statusStats = stub->GetDiskIOPS(&contextDiskStats, disk, &diskStatsResp);
	if (!stub)
		return diskStatsCtrl;
	return diskStatsResp;
}

mon::AllDiskResponse DiskMonitor::GetRequestSizeInBytesPerRead()
{
	google::protobuf::Empty empty;
	grpc::ClientContext context;
	grpc::Status statusDisks;
	mon::AllDiskResponse diskResponse;
	if (!stub)
		return diskResponse;
	statusDisks =
		stub->GetRequestSizeInBytesPerRead(&context, empty, &diskResponse);
	return diskResponse;
}

mon::DiskResponse
DiskMonitor::GetDiskRequestSizeInBytesPerRead(std::string name)
{
	grpc::Status statusStats;
	mon::DiskResponse diskStatsResp;
	mon::DiskResponse diskStatsCtrl;
	mon::DiskQ disk;
	grpc::ClientContext contextDiskStats;
	*disk.mutable_name() = name;
	statusStats = stub->GetDiskRequestSizeInBytesPerRead(&contextDiskStats,
														 disk, &diskStatsResp);
	if (!stub)
		return diskStatsCtrl;
	return diskStatsResp;
}

void DiskMonitor::CreateChannel(const std::string &ep)
{
	using grpc::Channel;
	std::shared_ptr<Channel> channel;
	channel = grpc::CreateChannel(ep, grpc::InsecureChannelCredentials());
	stub = DiskMonitoring::NewStub(channel);
}
