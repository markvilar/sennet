#include <boostnet/network.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/mutex.hpp>

#include <sl/Camera.hpp>

//-------------------------------------------------------------------------------

class CameraConnection : public Connection
{
private:
	sl::Camera* m_cam;

public:

private:
	void OnAccept(const std::string& host, boost::uint16_t port);
	void OnConnect(const std::string& host, boost::uint16_t port);
	void OnSend(const std::vector<boost::uint8_t>& buffer);
	void OnRecv(std::vector<boost::uint8_t>& buffer);
	void OnTimer(const boost::posix_time::time_duration& delta);
	void OnError(const boost::system::error_code& error);

public:
	CameraConnection(boost::shared_ptr<Hive> hive, sl::Camera* cam);
	~CameraConnection();
};

//-------------------------------------------------------------------------------

class CameraAcceptor : public Acceptor
{
private:

public:

private:
	bool OnAccept(boost::shared_ptr<Connection> connection, const std::string& host,
		boost::uint16_t port);
	void OnTimer(const boost::posix_time::time_duration& delta);
	void OnError(const boost::system::error_code& error);

public:
	CameraAcceptor(boost::shared_ptr<Hive> hive);
	~CameraAcceptor();
};

/*
//-------------------------------------------------------------------------------

class ImageConnection : public Connection
{
};

*/
