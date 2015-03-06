#pragma once

namespace WebDAV
{
	class Client
	{
		enum { buffer_size = 1000 * 1000 };

		void init();

		std::string webdav_hostname;
		std::string webdav_login;
		std::string webdav_password;

		std::string proxy_hostname;
		std::string proxy_login;
		std::string proxy_password;

		std::string cert_path;
		std::string key_path;

		std::map<std::string, std::string> options();

	public:

		/* Конструктор для соединения с WebDAV - сервером, c участием проски - сервера
		*  Входные параметры:
		*  webdav_hostname - строка, содержащая uri WebDAV - сервера
		*  webdav_login - логин пользователя от WebDAV - сервера
		*  webdav_password - пароль пользователя от WebDAV - сервера
		*  proxy_hostname - строка, содержащая uri прокси - сервера
		*  proxy_login - логин пользователя от прокси - сервера
		*  proxy_password - пароль пользователя от прокси - сервера */
		Client(std::map<std::string, std::string> options);

		/* Переопределенный деструктор по умолчанию */
		~Client();

		/* Метод возвращающий кол-во свободного места на WebDAV - сервере */
		long long free_size();

		/* Метод проверяющий наличие ресурса на WebDAV - сервере */
		bool check(std::string remote_resource = "/", std::string remote_root = "");

		/* Метод возвращающий информацию о ресурсе на WebDAV - сервере */
		std::map<std::string, std::string> info(std::string remote_resource, std::string remote_root = "");

		/* Метод удаления ресурса с WebDAV - сервера */
		bool clean(std::string remote_file, std::string remote_root = "");

		/* Метод проверяет является ли удаленный ресурс директорией */
		bool is_dir(std::string remote_resource, std::string remote_root);

		/* Метод возвращающий список ресурсов, содержащихся в директории WebDAV - сервера */
		std::vector<std::string> list(std::string remote_directory = "", std::string remote_root = "");

		/* Метод загрузки файла с WebDAV - сервера */
		bool download(std::string remote_file, std::wstring local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		/* Метод загрузки файла с WebDAV - сервера */
		bool download_to(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		/* Метод асинхронной загрузки файла с WebDAV - сервера */
		void async_download(std::string remote_file, std::wstring local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		/* Метод асинхронной загрузки файла с WebDAV - сервера */
		void async_download_to(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		/* Метод создания директории на WebDAV - сервере */
		bool create_directory(std::string remote_directory);

		/* Метод загрузки файла в директорию на WebDAV - сервер */
		bool upload(std::string remote_file, std::wstring local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		/* Метод загрузки файла в директорию на WebDAV - сервер */
		bool upload_from(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		/* Метод асинхронной загрузки файла в директорию на WebDAV - сервер */
		void async_upload(std::string remote_file, std::wstring local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		/* Метод асинхронной загрузки файла в директорию на WebDAV - сервер */
		void async_upload_from(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr);
	};
}