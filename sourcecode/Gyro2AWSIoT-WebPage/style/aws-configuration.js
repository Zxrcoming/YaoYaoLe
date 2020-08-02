/*
 * Copyright 2015-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/*
 * NOTE: You must set the following string constants prior to running this
 * example application.
 */
var awsConfiguration = {
  poolId: "us-east-1:3991d21a-9358-4cb3-8100-09601eae08e1", // 'YourCognitoIdentityPoolId'
  host: "ai75bgnyilhc6-ats.iot.us-east-1.amazonaws.com", // 'YourAwsIoTEndpoint', e.g. 'prefix.iot.us-east-1.amazonaws.com'
  region: "us-east-1", // 'YourAwsRegion', e.g. 'us-east-1'
};
module.exports = awsConfiguration;
