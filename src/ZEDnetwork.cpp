#include <ZEDutils/ZEDnetwork.hpp>

//-------------------------------------------------------------------------------

CameraConnection::CameraConnection(boost::shared_ptr<Hive> hive, 
	sl::Camera* cam) : Connection(hive), m_cam(cam)
{
}

CameraConnection::~CameraConnection()
{
}

void CameraConnection::OnAccept(const std::string& host, boost::uint16_t port)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port 
		<< std::endl;
	GetMutex()->unlock();
}

void CameraConnection::OnConnect(const std::string& host, boost::uint16_t port)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port 
		<< std::endl;
	GetMutex()->unlock();
}

void CameraConnection::OnSend(const std::vector<boost::uint8_t>& buffer)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << std::endl;
	GetMutex()->unlock();
}

void CameraConnection::OnRecv(std::vector<boost::uint8_t>& buffer)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << std::endl;
	GetMutex()->unlock();
}

void CameraConnection::OnTimer(const boost::posix_time::time_duration& delta)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " 
		<< boost::posix_time::to_simple_string(delta) << std::endl;
	GetMutex()->unlock();

}

void CameraConnection::OnError(const boost::system::error_code& error)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	GetMutex()->unlock();

}

//-------------------------------------------------------------------------------

CameraAcceptor::CameraAcceptor(boost::shared_ptr<Hive> hive) : Acceptor(hive)
{
}

CameraAcceptor::~CameraAcceptor()
{
}

bool CameraAcceptor::OnAccept(boost::shared_ptr<Connection> connection, 
	const std::string& host, boost::uint16_t port)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port
		<< std::endl;
	GetMutex()->unlock();
	return true;
}

void CameraAcceptor::OnTimer(const boost::posix_time::time_duration& delta)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " 
		<< boost::posix_time::to_simple_string(delta) << std::endl;
	GetMutex()->unlock();
}

void CameraAcceptor::OnError(const boost::system::error_code& error)
{
	GetMutex()->lock();
		std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	GetMutex()->unlock();
}
