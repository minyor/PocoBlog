
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

#include <libgupnp/gupnp-control-point.h>
#include <libgupnp/gupnp-context-manager.h>

#include <core/Header.h>
#include <core/Server.h>


using namespace core;


class UPnPPointThread: public Poco::Runnable
{
	Poco::Thread _thread;
	GMainLoop *_main_loop;
	std::string _interface;
	std::string _hostIP;

public:
	UPnPPointThread(std::string &interface, std::string &hostIP) : _interface(interface), _hostIP(hostIP)
	{
		_main_loop = NULL;
		_thread.start(*this);
	}

private:
	void addMapping(GUPnPControlPoint *cp, GUPnPServiceProxy *proxy, const char *protocol)
	{
		GError *error = NULL;

		std::string mappingDescription = std::string("Poco server ") +
			std::string(protocol) + std::to_string(server().conf().port());

		const gchar *remote_host = "";
		guint external_port = server().conf().portUPnP();
		//gchar *protocol;
		guint internal_port = server().conf().port();
		const gchar *internal_client = _hostIP.c_str();
		gboolean enabled = true;
		const gchar *description = mappingDescription.c_str();
		guint lease_duration = 0;

		error = NULL;
		gupnp_service_proxy_send_action(proxy, "AddPortMapping", &error, "NewRemoteHost",
			G_TYPE_STRING, remote_host, "NewExternalPort", G_TYPE_UINT, external_port, "NewProtocol",
			G_TYPE_STRING, protocol, "NewInternalPort", G_TYPE_UINT, internal_port, "NewInternalClient",
			G_TYPE_STRING, internal_client, "NewEnabled", G_TYPE_BOOLEAN, enabled, "NewPortMappingDescription",
			G_TYPE_STRING, description, "NewLeaseDuration", G_TYPE_UINT, lease_duration, NULL, NULL);

		if(error)
		{
			printf("Error: AddPortMapping: %s (%u)\n", error->message, error->code);
			g_error_free(error);
			return;
		}

		printf("new mapping: %s '%s' %u %u %s\n", _interface.c_str(), internal_client, internal_port, external_port, protocol);
	}

	void serviceProxy(GUPnPControlPoint *cp, GUPnPServiceProxy *proxy)
	{
		GError *error = NULL;

		/*gchar *connection_status, *last_connection_error;
		guint uptime;
		gupnp_service_proxy_send_action(proxy, "GetStatusInfo", &error, NULL, "NewConnectionStatus", G_TYPE_STRING,
			&connection_status, "NewLastConnectionError", G_TYPE_STRING, &last_connection_error,
			"NewUptime", G_TYPE_UINT, &uptime, NULL);

		if(error)
		{
			g_printerr("Error: GetStatusInfo: %s (%u)\n", error->message, error->code);
			g_error_free(error);
			return;
		}

		g_print("Connection Status:   %s\n", connection_status);
		g_print("Uptime:              %uh%02um%02us\n", uptime/3600, (uptime/60)%60, uptime%60);
		g_free(connection_status);
		g_free(last_connection_error);*/


		/*gchar *ip = NULL;
		error = NULL;
		gupnp_service_proxy_send_action(proxy, "GetExternalIPAddress", &error, NULL, "NewExternalIPAddress",
			G_TYPE_STRING, &ip, NULL);

		if (error)
		{
			g_printerr("Error: GetExternalIPAddress: %s (%u)\n", error->message, error->code);
			g_error_free(error);
			return;
		}

		g_print("External IP address: %s\n", ip);
		g_free(ip);*/


		bool portExists = false;
		for(guint index=0; ; ++index)
		{
			gchar *remote_host, *protocol, *internal_client, *description;
			guint external_port, internal_port, lease_duration;
			gboolean enabled;

			error = NULL;
			gupnp_service_proxy_send_action(proxy, "GetGenericPortMappingEntry", &error, "NewPortMappingIndex",
				G_TYPE_UINT, index, NULL, "NewRemoteHost", G_TYPE_STRING, &remote_host, "NewExternalPort",
				G_TYPE_UINT, &external_port, "NewProtocol", G_TYPE_STRING, &protocol, "NewInternalPort",
				G_TYPE_UINT, &internal_port, "NewInternalClient", G_TYPE_STRING, &internal_client, "NewEnabled",
				G_TYPE_BOOLEAN, &enabled, "NewPortMappingDescription", G_TYPE_STRING, &description, "NewLeaseDuration",
				G_TYPE_UINT, &lease_duration, NULL);

			if(error)
			{
				if(error->code != 713) // end of ports array
					printf("Error: GetGenericPortMappingEntry: %s (%u)\n", error->message, error->code);
				g_error_free(error);
				break;
			}

			printf("mapping: %s '%s' %u %u %s\n", _interface.c_str(), internal_client, internal_port, external_port, protocol);
			if(internal_port == server().conf().port())
				portExists = true;

			g_free(remote_host);
			g_free(protocol);
			g_free(internal_client);
			g_free(description);
		}

		if(!portExists)
		{
			addMapping(cp, proxy, "TCP");
			//addMapping(cp, proxy, "UDP");
		}
	}


	void listServices(GUPnPControlPoint *cp, GUPnPDeviceInfo *info)
	{
		GList *services = gupnp_device_info_list_services(info);
		for(GList *l=services; l; l=l->next)
		{
			const char *serviceType = gupnp_service_info_get_service_type((GUPnPServiceInfo *)l->data);
			if (!g_strcmp0(serviceType, "urn:schemas-upnp-org:service:WANIPConnection:1") ||
				!g_strcmp0(serviceType, "urn:schemas-upnp-org:service:WANPPPConnection:1"))
			{
				serviceProxy(cp, GUPNP_SERVICE_PROXY((GUPnPServiceInfo *)l->data));
			}
		}
	}

	static void available(GUPnPControlPoint *cp, GUPnPDeviceProxy *proxy, gpointer data)
	{
		UPnPPointThread &me = *(UPnPPointThread *)data; (void)me;

		me.listServices(cp, GUPNP_DEVICE_INFO(proxy));

		//g_main_loop_quit(me._main_loop);
	}

public:
	void run()
	{
		GError *error = NULL;
		GUPnPContext *context = gupnp_context_new(NULL, _interface.c_str(), 0, &error);
		if(error)
		{
			printf("Error: gupnp_context_new(): %s (%u)\n", error->message, error->code);
			return;
		}

		GUPnPControlPoint *point = gupnp_control_point_new(context, "urn:schemas-upnp-org:device:InternetGatewayDevice:1");
		g_signal_connect(point, "device-proxy-available", G_CALLBACK(available), this);
		gssdp_resource_browser_set_active(GSSDP_RESOURCE_BROWSER(point), TRUE);

		/*do {
			GstMessage *msg = gst_bus_timed_pop(bus, -1);
			gst_message_unref(msg);
		} while (_running);*/

		GMainContext *mcontext = g_main_context_new();
		g_main_context_push_thread_default(mcontext);
		_main_loop = g_main_loop_new(mcontext, FALSE);
		g_main_loop_run(_main_loop);
		g_main_loop_unref(_main_loop);
		g_main_context_unref(mcontext);

		g_object_unref(point);
		g_object_unref(context);

		//std::unique_ptr<Poco::Thread> thread = std::move(_thread);
		delete this;
	}

};


class UPnPThread: public Poco::Runnable
{
	Poco::Thread _thread;
	GMainLoop *_main_loop;

public:
	UPnPThread()
	{
		_main_loop = NULL;
		_thread.start(*this);
	}

private:
	static void available(GUPnPContextManager *context_manager, GUPnPContext *context, gpointer data)
	{
		UPnPThread &me = *(UPnPThread *)data; (void)me;
		GSSDPClient *client = GSSDP_CLIENT(context);

		std::string serverId = gssdp_client_get_server_id(client);	(void)serverId;
		std::string interface = gssdp_client_get_interface(client);	(void)interface;
		std::string hostIP = gssdp_client_get_host_ip(client);		(void)hostIP;
		std::string network = gssdp_client_get_network(client);		(void)network;
		bool active = gssdp_client_get_active(client);				(void)active;

		printf("interface: '%s'; hostIP: '%s'\n", interface.c_str(), hostIP.c_str());
		new UPnPPointThread(interface, hostIP);
	}

	static void unavailable(GUPnPContextManager *context_manager, GUPnPContext *context, gpointer data)
	{
		UPnPThread &me = *(UPnPThread *)data; (void)me;
	}

public:
	void run()
	{
		while(!server().conf().portUPnP()) _thread.sleep(100);

		printf("UPnP Context begin\n");
		GUPnPContextManager *contextManager = gupnp_context_manager_create(0);

		g_signal_connect(contextManager, "context-available", G_CALLBACK(available), this);
		g_signal_connect(contextManager, "context-unavailable", G_CALLBACK(unavailable), this);

		_main_loop = g_main_loop_new(NULL, FALSE);
		g_main_loop_run(_main_loop);
		g_main_loop_unref(_main_loop);

		g_object_unref(contextManager);

		printf("UPnP Context end\n");
	}

};


static UPnPThread &UPnP()
{
	static UPnPThread thread;
	return thread;
}

void core::initUPnP()
{
	static bool initialized = false;
	if(initialized) return;
	initialized = true;

	UPnP();
}