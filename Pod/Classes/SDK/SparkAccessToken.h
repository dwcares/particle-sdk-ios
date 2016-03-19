//
//  SparkAccessToken.h
//  Particle iOS Cloud SDK
//
//  Created by Ido Kleinman
//  Copyright 2015 Particle
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SparkAccessToken;

@protocol SparkAccessTokenDelegate <NSObject>

@required
-(void)sparkAccessToken:(SparkAccessToken *)accessToken didExpireAt:(NSDate *)date;

@end

@interface SparkAccessToken : NSObject

/**
 *  Access token string to be used when calling cloud API
 */
@property (nonatomic, strong, nullable, readonly) NSString *accessToken;

/**
 *  Delegate to receive didExpireAt method call whenever a token is detected as expired
 */
@property (nonatomic, nullable, weak) id<SparkAccessTokenDelegate> delegate;

/**
 *  Initialze SparkAccessToken class with new session
 *
 *  @param loginResponseDict response object from Spark cloud login deserialized as NSDictionary
 *
 *  @return New SparkAccessToken instance
 */
-(nullable instancetype)initWithNewSession:(NSDictionary *)loginResponseDict;

// For two Legged Auth you can init SparkAccessToken with access token only/with exact expiry date/with refresh token:
-(nullable instancetype)initWithToken:(NSString *)token;
-(nullable instancetype)initWithToken:(NSString *)token andExpiryDate:(NSDate *)expiryDate;
-(nullable instancetype)initWithToken:(NSString *)token withExpiryDate:(NSDate *)expiryDate withRefreshToken:(NSString *)refreshToken;

/**
 *  Initialize SparkAccessToken from existing session stored in keychain
 *
 *  @return A SparkAccessToken instance in case session is stored in keychain and token has not expired, nil if not
 */
-(nullable instancetype)initWithSavedSession;

-(instancetype)init __attribute__((unavailable("Must use initWithNewSession: / initWithSavedSession: or one of the initWithToken initializers")));

/**
 *  Remove access token session data from keychain
 */
-(void)removeSession;

@end

NS_ASSUME_NONNULL_END
