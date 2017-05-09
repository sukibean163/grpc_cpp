/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <iostream>

#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;
using namespace helloworld;

#include "yolo.h"
#include <opencv2/opencv.hpp>
using namespace cv;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service
{
public:
  GreeterServiceImpl()
  {
  }
  Status SayHello(ServerContext *context, const HelloRequest *request,
                  HelloReply *reply) override
  {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }

  Status yolo_detect(::grpc::ServerContext *context, const ::helloworld::DetectRequest *request, ::helloworld::DetectResponse *response)
  {
    std::cout << "Received2 yolo_detect	" << request->img_name() << std::endl;

    // imshow("xx", img);
    // waitKey(0);
    // std::vector<DetectedObject> detection;
    // yolo.detect(img, detection);

    // for (int i = 0; i < detection.size(); i++)
    {
      DetectedObject o;
      o.object_class = "xx";
      int i = 0;
      o.bounding_box.x = i;
      i++;
      o.bounding_box.y = i;
      i++;
      o.bounding_box.width = i;
      i++;
      o.bounding_box.height = i;
      i++;
      //        cv::rectangle(img, o.bounding_box, cv::Scalar(255, 0, 0), 2);

      DetectData *res = response->add_data();
      res->set_type(o.object_class);
      // res->set_x(1 * i);
      // res->set_y(2 * i);
      // res->set_width(3 * i);
      // res->set_height(4 * i);

      res->set_x(o.bounding_box.x);
      res->set_y(o.bounding_box.y);
      res->set_width(o.bounding_box.width);
      res->set_height(o.bounding_box.height);
    }
    std::cout << response->data_size() << std::endl;

    return Status::OK;
  }
};

void RunServer()
{
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char **argv)
{
  RunServer();

  return 0;
}