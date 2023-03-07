//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

//this is a construct that prints out the exact time/day/month and year
std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try
  {
    // Create an io_context object to perform operations to run the eventbased loops.
    boost::asio::io_context io_context;

    // Create an acceptor object and open the acceptor.
    // The acceptor object accept and listen for new connections on TCP port 13.
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true)
    {
      // This will connnect two networks
      tcp::socket socket(io_context);
      acceptor.accept(socket);
      // This will print the time, day, month and year.
      std::string message = make_daytime_string();

      // This will send the message to the client and it will ignore any potential errors.
      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}