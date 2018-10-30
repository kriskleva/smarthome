/**
 * Copyright 2016, Google, Inc.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

'use strict';
const Datastore = require('@google-cloud/datastore');

// Instantiates a client
const datastore = Datastore();

/**
 * Get the sensor value and returns the fulfillmentText.
 * @param {object} res Cloud Function response context.
 */
exports.get = (req, res) => {
  const key = getKeyFromRequestData({"kind":"Telemetry","key":"sensor"});

  return datastore.get(key)
    .then(([entity]) => {
      res.status(200).send(JSON.stringify({ 'fulfillmentText': "Here is your Sensor Value: " + entity.message}));
    })
    .catch((err) => {
      console.error(err);
      res.status(200).send(err.message);
      return Promise.reject(err);
    });
};

/**
 * Triggered from a message on a Cloud Pub/Sub topic.
 *
 * @param {!Object} event Event payload and metadata.
 * @param {!Function} callback Callback function to signal completion.
 */
exports.post = (event, callback) => {
  const pubsubMessage = event.data;
  var req_body = {"kind":"Telemetry","key":"sensor"};
  var message = Buffer.from(pubsubMessage.data, 'base64').toString();
  const key = getKeyFromRequestData(req_body);
  const entity = {
    key: key,
    data: {"message":message}
  };
  var save = datastore.save(entity);
  callback();
};

function getKeyFromRequestData (requestData) {
  if (!requestData.key) {
    throw new Error('Key not provided. Make sure you have a "key" property in your request');
  }

  if (!requestData.kind) {
    throw new Error('Kind not provided. Make sure you have a "kind" property in your request');
  }

  return datastore.key([requestData.kind, requestData.key]);
}
