//
//  NOServer.h
//  NetworkObjects
//
//  Created by Alsey Coleman Miller on 9/29/13.
//  Copyright (c) 2013 CDA. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import <NetworkObjects/NOServerConstants.h>

@class NOStore, RouteRequest, RouteResponse, NOHTTPServer;

@protocol NOResourceProtocol;
@protocol NOSessionProtocol;

@interface NOServer : NSObject

-(id)initWithStore:(NOStore *)store
    userEntityName:(NSString *)userEntityName
 sessionEntityName:(NSString *)sessionEntityName
  clientEntityName:(NSString *)clientEntityName
         loginPath:(NSString *)loginPath;

@property (readonly) NOStore *store;

@property (readonly) NOHTTPServer *httpServer;

@property (readonly) NSString *sessionEntityName;

@property (readonly) NSString *userEntityName;

@property (readonly) NSString *clientEntityName;

@property (readonly) NSString *loginPath;

-(NSError *)startOnPort:(NSUInteger)port;

-(void)stop;

@property (readonly) NSDictionary *resourcePaths;

-(void)setupServerRoutes;

@property BOOL prettyPrintJSON;

#pragma mark - Responding to requests

// code for handling incoming REST requests (authentication, returning JSON data)
-(void)handleRequest:(RouteRequest *)request
forResourceWithEntityDescription:(NSEntityDescription *)entityDescription
          resourceID:(NSNumber *)resourceID
            function:(NSString *)functionName
            response:(RouteResponse *)response;

-(void)handleCreateResourceWithEntityDescription:(NSEntityDescription *)entityDescription
                                         session:(NSManagedObject<NOSessionProtocol> *)session
                                   initialValues:(NSDictionary *)initialValues
                                        response:(RouteResponse *)response;

-(void)handleFunction:(NSString *)functionName
   recievedJsonObject:(NSDictionary *)recievedJsonObject
             resource:(NSManagedObject<NOResourceProtocol> *)resource
              session:(NSManagedObject<NOSessionProtocol> *)session
             response:(RouteResponse *)response;

-(void)handleEditResource:(NSManagedObject <NOResourceProtocol> *)resource
       recievedJsonObject:(NSDictionary *)recievedJsonObject
                  session:(NSManagedObject <NOSessionProtocol> *)session
                 response:(RouteResponse *)response;

-(void)handleGetResource:(NSManagedObject <NOResourceProtocol> *)resource
                 session:(NSManagedObject <NOSessionProtocol> *)session
                response:(RouteResponse *)response;

-(void)handleDeleteResource:(NSManagedObject <NOResourceProtocol> *)resource
                    session:(NSManagedObject <NOSessionProtocol> *)session
                   response:(RouteResponse *)response;

-(void)handleLoginWithRequest:(RouteRequest *)request
                     response:(RouteResponse *)response;

#pragma mark - Common methods for handlers

-(NSManagedObject<NOSessionProtocol> *)sessionWithToken:(NSString *)token;

-(NSDictionary *)JSONRepresentationOfResource:(NSManagedObject<NOResourceProtocol> *)resource
                                   forSession:(NSManagedObject<NOSessionProtocol> *)session;

-(NOServerStatusCode)verifyEditResource:(NSManagedObject<NOResourceProtocol> *)resource
                     recievedJsonObject:(NSDictionary *)recievedJsonObject
                                session:(NSManagedObject<NOSessionProtocol> *)session;

-(void)setValuesForResource:(NSManagedObject<NOResourceProtocol> *)resource
             fromJSONObject:(NSDictionary *)jsonObject
                    session:(NSManagedObject<NOSessionProtocol> *)session;


@end