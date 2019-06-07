//
//  MyController.hpp
//  web-starter-project
//
//  Created by Leonid on 2/12/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef MyController_hpp
#define MyController_hpp

#include "oatpp-websocket/Handshaker.hpp"

#include "oatpp/web/server/api/ApiController.hpp"

#include "oatpp/network/server/ConnectionHandler.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

/**
 * Controller with WebSocket-connect endpoint.
 */
class MyController : public oatpp::web::server::api::ApiController {
private:
  typedef MyController __ControllerType;
private:
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::server::ConnectionHandler>, websocketConnectionHandler, "websocket");
public:
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:
  
/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)
  
  ENDPOINT_ASYNC("GET", "/", Root) {
    
    ENDPOINT_ASYNC_INIT(Root)

    const char* pageTemplate =
      "<html lang='en'>"
        "<head>"
          "<meta charset=utf-8/>"
        "</head>"
        "<body>"
          "<p>Hello Async WebSocket Server!</p>"
          "<p>"
            "<code>websocket endpoint is: localhost:8000/ws</code>"
          "</p>"
        "</body>"
      "</html>";

    Action act() override {
      return _return(controller->createResponse(Status::CODE_200, pageTemplate));
    }
    
  };

  ENDPOINT_ASYNC("GET", "ws", WS) {

    ENDPOINT_ASYNC_INIT(WS)

    Action act() override {
      auto response = oatpp::websocket::Handshaker::serversideHandshake(request->getHeaders(), controller->websocketConnectionHandler);
      return _return(response);
    }

  };
  
  // TODO Insert Your endpoints here !!!
  
/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)
  
};

#endif /* MyController_hpp */
