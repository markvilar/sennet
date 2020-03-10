#include <ZEDutils/ZEDnetwork.hpp>

//-------------------------------------------------------------------------------

ImageConnection::ImageConnection(boost::shared_ptr<Hive> hive) : Connection(hive)
{
}

ImageConnection::~ImageConnection()
{
}

void ImageConnection::OnAccept(const std::string& host, boost::uint16_t port)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port 
		<< std::endl;
	GetMutex()->unlock();
}

void ImageConnection::OnConnect(const std::string& host, boost::uint16_t port)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port 
		<< std::endl;
	GetMutex()->unlock();
}

void ImageConnection::OnSend(const std::vector<boost::uint8_t>& buffer)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << std::endl;
	GetMutex()->unlock();
}

void ImageConnection::OnRecv(std::vector<boost::uint8_t>& buffer)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << std::endl;
	GetMutex()->unlock();
}

void ImageConnection::OnTimer(const boost::posix_time::time_duration& delta)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " 
		<< boost::posix_time::to_simple_string(delta) << std::endl;
	GetMutex()->unlock();

}

void ImageConnection::OnError(const boost::system::error_code& error)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	GetMutex()->unlock();

}

//-------------------------------------------------------------------------------

ControlAcceptor::ControlAcceptor(boost::shared_ptr<Hive> hive) : Acceptor(hive)
{
}

ControlAcceptor::~ControlAcceptor()
{
}

bool ControlAcceptor::OnAccept(boost::shared_ptr<Connection> connection, 
	const std::string& host, boost::uint16_t port)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port
		<< std::endl;
	GetMutex()->unlock();
	return true;
}

void ControlAcceptor::OnTimer(const boost::posix_time::time_duration& delta)
{
	GetMutex()->lock();
	std::cout << "[" << __FUNCTION__ << "] " 
		<< boost::posix_time::to_simple_string(delta) << std::endl;
	GetMutex()->unlock();
}

void ControlAcceptor::OnError(const boost::system::error_code& error)
{
	GetMutex()->lock();
		std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	GetMutex()->unlock();
}
