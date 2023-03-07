//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>

using boost::asio::ip::tcp;

//sets the size of the image, we choose these values by the pictures properties
constexpr size_t image_size = 480*360;

void save_image(char* data, size_t len)
{
  static int image_count = 0;
  std::string filename = "copycat" + std::to_string(image_count) + ".jpg";
  std::ofstream file(filename, std::ios::out | std::ios::binary);
  file.write(data, len);
  file.close();
  image_count++;
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while(true)
    {
      boost::array<char, image_size> buf;
      boost::system::error_code error;

      // read until buffer is full
      boost::asio::read(socket,boost::asio::buffer(buf));

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      save_image(buf.data(),image_size);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}