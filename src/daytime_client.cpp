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

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments, if not enough, print usage and exit with error.
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    // Create a context for the io_service.
    boost::asio::io_context io_context;

    
    // Get a list of endpoints corresponding to the server name.
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    // Try each endpoint until we successfully establish a connection.
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    
    while(true)
    {
      // Read until newline.
      boost::array<char, 128> buf;
      boost::system::error_code error;

      // Read some data. The read function will block until one or more bytes of
      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      // If we get here, the connection is closed cleanly by the peer.
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      // Write the data we received to standard output.
      std::cout.write(buf.data(), len);
    }
  }

  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}