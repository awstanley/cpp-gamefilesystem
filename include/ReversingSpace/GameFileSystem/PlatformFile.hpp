/*
 * Copyright 2017-2018 ReversingSpace. See the COPYRIGHT file at the
 * top-level directory of this distribution and in the repository:
 * https://github.com/ReversingSpace/cpp-gamefilesystem
 *
 * Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
 * http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
 * <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
 * option. This file may not be copied, modified, or distributed
 * except according to those terms.
**/

#ifndef REVERSINGSPACE_GAMEFILESYSTEM_PLATFORMFILE_HPP
#define REVERSINGSPACE_GAMEFILESYSTEM_PLATFORMFILE_HPP

#include <ReversingSpace/GameFileSystem/Core.hpp>
#include <ReversingSpace/GameFileSystem/File.hpp>
#include <ReversingSpace/Storage/File.hpp>

#include <shared_mutex>

namespace reversingspace {
	namespace gfs {
		/**
		 * @brief Storage backed Platform File.
		 *
		 * This pulls views on the fly to perform its operations, so it
		 * functions in a non-insert mode.  This is kind of less than ideal
		 * and you should create an archive type to handle this better
		 * (where possible).
		 */
		class REVSPACE_GAMEFILESYSTEM_API PlatformFile : public File {
		private:
			/// Memory-mapped file.
			storage::FilePointer stored_file;

			/// Cursor
			storage::StorageSize cursor;

			/// Read/write mutex.
			std::shared_mutex rw_mutex;

		public: // File

			/**
			 * Sets the cursor position.
			 *
			 * This method will lock the internal mutex for WRITE as it modifies
			 * the internal cursor.
			 *
			 * @param[in] offset Offset from the point of origin.
			 * @param[in] whence Point of origin ('whence') for the seek.
			 * @return Current offset (unsigned as it canno be negative).
			 */
			storage::StorageSize seek(storage::StorageOffset offset,
				storage::Seek whence = storage::Seek::Set);

			/**
			 * @brief Gets the view size (in bytes).
			 * @return View size, in bytes.
			 *
			 * This is designed to be used with `get_data_pointer`.
			 */
			storage::StorageSize get_size() const {
				return stored_file->get_size();
			}

			/**
			 * @brief Returns the current offset in the file.
			 */
			inline storage::StorageOffset tell() const {
				return cursor;
			}

			/**
			 * @brief Reads from the cursor position.
			 * @oaram[out] data Pointer to preallocated buffer (for storage).
			 * @param[in] requested Number of bytes requested.
			 * @return number of bytes read.
			 *
			 * This method will lock the internal mutex for WRITE as it moves
			 * the cursor.
			 */
			storage::StorageSize read(char* data,
				storage::StorageSize requested);

			/**
			 * @brief Reads data from a file into a vector.
			 * @oaram[out] data Vector for storing data.
			 * @param[in] requested Number of bytes requested.
			 * @return number of bytes read.
			 */
			storage::StorageSize read(std::vector<std::uint8_t>& data,
				storage::StorageSize requested);

			/**
			 * @brief Reads from a specific offset in the view, storing it in the buffer.
			 * @param[in] offset  Offset (from the start of the view).
			 * @oaram[out] data Pointer to preallocated buffer (for storage).
			 * @param[in] requested Number of bytes requested.
			 * @return number of bytes read.
			 */
			storage::StorageSize read_from(storage::StorageOffset offset,
				char* data, storage::StorageSize requested);

			/**
			 * @brief Reads data from a file into a vector.
			 * @param[in] offset  Offset (from the start of the view).
			 * @oaram[out] data Vector for storing data.
			 * @param[in] requested Number of bytes requested.
			 * @return number of bytes read.
			 */
			storage::StorageSize read_from(storage::StorageOffset offset,
				std::vector<std::uint8_t>& data,
				storage::StorageSize requested);

			/**
			 * @brief Write a requested number of bytes into a file instance.
			 * This writes to the end of the data stream (using 'cursor').
			 * @param[in,out] data Pointer to data (buffer) to be written.
			 * @param[in] requested Number of bytes requested.
			 * @return number of bytes written.
			 */
			storage::StorageSize write(char* data,
				storage::StorageSize requested);

			/**
			 * @brief Reads data into a file from a vector.
			 * This writes to the end of the data stream (using 'cursor').
			 * @param[in,out] data Vector into which data is stored.
			 * @param[in] requested Number of bytes requested.
			 * @return number of bytes written.
			 */
			storage::StorageSize write(std::vector<std::uint8_t>& data,
				storage::StorageSize requested);

			/**
			 * @brief Write a requested number of bytes into a file instance.
			 * This writes to the given offset, only updating 'cursor' if it is exceeded.
			 * @param[in] offset  Offset (from the start of the view).
			 * @param[in,out] data Pointer to data (storage/buffer).
			 * @param[in] requested Number of bytes requested.
			 * @return number of bytes written.
			 */
			storage::StorageSize write_to(storage::StorageOffset offset,
				char* data, storage::StorageSize requested);

			/**
			 * @brief Reads data into a file from a vector.
			 * This writes to the given offset, only updating 'cursor' if it is exceeded.
			 * @param[in] offset  Offset (from the start of the view).
			 * @param[in,out] data Vector into which data is stored.
			 * @param[in] requested Number of bytes requested.
			 * @return number of bytes written.
			 */
			storage::StorageSize write_to(storage::StorageOffset offset,
				std::vector<std::uint8_t>& data,
				storage::StorageSize requested);
		};
	}
}

#endif//REVERSINGSPACE_GAMEFILESYSTEM_PLATFORMFILE_HPP