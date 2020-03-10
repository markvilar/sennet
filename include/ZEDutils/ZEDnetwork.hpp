#include <boostnet/network.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/mutex.hpp>

#include <sl/Camera.hpp>

//-------------------------------------------------------------------------------

class ImageConnection: public Connection
{
private:

public:

private:
	void OnAccept(const std::string& host, boost::uint16_t port);
	void OnConnect(const std::string& host, boost::uint16_t port);
	void OnSend(const std::vector<boost::uint8_t>& buffer);
	void OnRecv(std::vector<boost::uint8_t>& buffer);
	void OnTimer(const boost::posix_time::time_duration& delta);
	void OnError(const boost::system::error_code& error);

public:
	ImageConnection(boost::shared_ptr<Hive> hive);
	~ImageConnection();
};

//-------------------------------------------------------------------------------

class ControlAcceptor: public Acceptor
{
private:

public:

private:
	bool OnAccept(boost::shared_ptr<Connection> connection, 
		const std::string& host, boost::uint16_t port);
	void OnTimer(const boost::posix_time::time_duration& delta);
	void OnError(const boost::system::error_code& error);

public:
	ControlAcceptor(boost::shared_ptr<Hive> hive);
	~ControlAcceptor();
};
