/*#***************************************************************************
#                         __    __   _____       _____
#   Project              |  |  |  | |     \     /  ___|
#                        |  |__|  | |  |\  \   /  /
#                        |        | |  | )  ) (  (     
#                        |   /\   | |  |/  /   \  \___
#                         \_/  \_/  |_____/     \_____|
#
# Copyright (C) 2016, The WDC Project, <designerror@yandex.ru>, et al.
#
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution. 
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the LICENSE file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
############################################################################*/

#ifndef WEBDAV_CLIENT_HPP
#define WEBDAV_CLIENT_HPP

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace WebDAV
{
	using progress_t = std::function<int(void *context,
								size_t dltotal,
								size_t dlnow, 
								size_t ultotal, 
								size_t ulnow)> ;

	using callback_t = std::function<void(bool)> ;

	using strings_t = std::vector<std::string>;
	using dict_t = std::map<std::string, std::string>;

	///
	/// \brief WebDAV Client
	/// \author designerror
	/// \version 1.1.0
	/// \date 08/8/2016
	///
	class Client
	{	
	public:

		///
		/// \param[in] webdav_hostname
		/// \param[in] webdav_root
		/// \param[in] webdav_username
		/// \param[in] webdav_password
		/// \param[in] proxy_hostname
		/// \param[in] proxy_username
		/// \param[in] proxy_password
		/// \param[in] cert_path
		/// \param[in] key_path
		/// \include client/init.cpp
		///
		explicit Client(const dict_t& options);

		///
		/// Get free size of the WebDAV server
		/// \return size in bytes
		/// \include client/size.cpp
		///
		auto free_size() const noexcept -> unsigned long long;

		///
		/// Check for existence of a remote resource
		/// \param[in] remote_resource
		/// \include client/check.cpp
		///
		auto check(const std::string& remote_resource = "/") const noexcept -> bool;

		///
		/// Get information of a remote resource
		/// \param[in] remote_resource
		/// \include client/info.cpp
		///
		auto info(const std::string& remote_resource) const noexcept -> dict_t;

		///
		/// Clean an remote resource
		/// \param[in] remote_resource
		/// \include client/clean.cpp
		///
		auto clean(const std::string& remote_resource) const noexcept -> bool;

		///
		/// Checks whether the resource directory
		/// \param[in] remote_resource
		///
		auto is_directory(const std::string& remote_resource) const noexcept -> bool;

		///
		/// List a remote directory
		/// \param[in] remote_directory
		/// \include client/list.cpp
		///
		auto list(const std::string& remote_directory = "") const noexcept -> strings_t;

		///
		/// Create a remote directory
		/// \param[in] remote_directory
		/// \param[in] recursive
		/// \include client/mkdir.cpp
		///
		auto create_directory(
			const std::string& remote_directory, 
			bool recursive = false
		) const noexcept -> bool;

		///
		/// Move a remote resource
		/// \param[in] remote_source_resource
		/// \param[in] remote_destination_resource
		/// \include client/move.cpp
		///
		auto move(
			const std::string& remote_source_resource, 
			const std::string& remote_destination_resource
		) const noexcept -> bool;

		///
		/// Copy a remote resource
		/// \param[in] remote_source_resource
		/// \param[in] remote_destination_resource
		/// \include client/copy.cpp
		///
		auto copy(
			const std::string& remote_source_resource, 
			const std::string& remote_destination_resource
		) const noexcept -> bool;

		///
		/// Download a remote file to a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] progress
		/// \snippet client/download.cpp download_to_file
		///
		auto download(
			const std::string& remote_file, 
			const std::string& local_file, 
			progress_t progress = nullptr
		) const noexcept -> bool;

		///
		/// Download a remote file to a buffer
		/// \param[in] remote_file
		/// \param[out] buffer_ptr
		/// \param[out] buffer_size
		/// \param[in] progress
		/// \snippet client/download.cpp download_to_buffer
		///
		auto download_to(
			const std::string& remote_file,
			char * & buffer_ptr, 
			unsigned long long & buffer_size, 
			progress_t progress = nullptr
		) const noexcept -> bool;

		///
		/// Download a remote file to a stream
		/// \param[in] remote_file
		/// \param[out] stream
		/// \param[in] progress
		/// \snippet client/download.cpp download_to_stream
		///
		auto download_to(
			const std::string& remote_file,
			std::ostream& stream,
			progress_t progress = nullptr
		) const noexcept -> bool;

		///
		/// Asynchronously download a remote file to a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] callback
		/// \param[in] progress
		/// \snippet client/download.cpp async_download_to_file
		///
		auto async_download(
			const std::string& remote_file, 
			const std::string& local_file, 
			callback_t callback = nullptr, 
			progress_t progress = nullptr
		) const noexcept -> void;

		///
		/// Upload a remote file from a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] progress
		/// \snippet client/upload.cpp upload_from_file
		///
		auto upload(
			const std::string& remote_file,
			const std::string& local_file, 
			progress_t progress = nullptr
		) const noexcept -> bool;

		///
		/// Upload a remote file from a buffer
		/// \param[in] remote_file
		/// \param[in] buffer_ptr
		/// \param[in] buffer_size
		/// \param[in] progress
		/// \snippet client/upload.cpp upload_from_buffer
		///
		auto upload_from(
			const std::string& remote_file, 
			char * buffer_ptr, 
			unsigned long long buffer_size, 
			progress_t progress = nullptr
		) const noexcept -> bool;

		///
		/// Upload a remote file from a stream
		/// \param[in] remote_file
		/// \param[in] stream
		/// \param[in] progress
		/// \snippet client/upload.cpp upload_from_stream
		///
		auto upload_from(
			const std::string& remote_file, 
			std::istream& stream, 
			progress_t progress = nullptr
		) const noexcept -> bool;

		///
		/// Asynchronously upload a remote file from a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] callback
		/// \param[in] progress
		/// \snippet client/upload.cpp async_upload_from_file
		///
		auto async_upload(
			const std::string& remote_file, 
			const std::string& local_file, 
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept -> void;
        
	private:

		auto sync_download(
			const std::string& remote_file,
			const std::string& local_file,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept -> bool;

		auto sync_download_to(
			const std::string& remote_file,
			char * & buffer_ptr,
			unsigned long long int & buffer_size,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept -> bool;

		bool sync_download_to(
			const std::string& remote_file,
			std::ostream& stream,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept;

		bool sync_upload(
			const std::string& remote_file,
			const std::string& local_file,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept;

		auto sync_upload_from(
			const std::string& remote_file,
			char * buffer_ptr,
			unsigned long long int buffer_size,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept -> bool;

		auto sync_upload_from(
			const std::string& remote_file,
			std::istream& stream,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept -> bool;

		enum { buffer_size = 1000 * 1000 };

		std::string webdav_hostname;
		std::string webdav_root;
		std::string webdav_username;
		std::string webdav_password;

		std::string proxy_hostname;
		std::string proxy_username;
		std::string proxy_password;

		std::string cert_path;
		std::string key_path;

		dict_t options() const noexcept;
	};
}

#endif
