#include "webservice.h"

DUDA_REGISTER("Duda I/O Examples", "rpi");

void cb_hello(duda_request_t *dr)
{
   response->http_status(dr, 200);
	 //call the system to record the ifconfig info
   response->printf(dr, "it works \n"
			 									"http://localhost:2001/rpi_REST/temp      for tempture info \n"
												"http://localhost:2001/rpi_REST/ifconfig  for ip info");
   response->end(dr, NULL);
}

void cb_ifconfig(duda_request_t *dr) 
{
		response->http_status(dr, 200);
	  system("ifconfig > ~/pi");
		response->printf(dr, "Your Pi's temp is: \n");
		response->sendfile(dr, "/home/root/pi");
    response->end(dr, NULL);
}

void cb_temp(duda_request_t *dr)
{
		response->http_status(dr, 200);
	  system("/opt/vc/bin/vcgencmd measure_temp > ~/pi");
   /*
   	*Test is based on Arch Linux ARM-Raspberry
		*vcgencmd can test the tempture of Pi directly*/
		response->printf(dr, "Your Pi is Running at: \n");
		response->sendfile(dr, "/home/root/pi");
    response->end(dr, NULL);
}

int duda_main()
{
		map->static_add("/temp", "cb_temp");
		map->static_add("/ifconfig", "cb_ifconfig");
    map->static_add("/", "cb_hello");
    return 0;
}
