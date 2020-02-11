#include <sl/Camera.hpp>

class ZEDReceiver
{
	private:
	public:
		ZEDReceiver();
		~ZEDReceiver();
		sl::ERROR_CODE listen() const;
};
