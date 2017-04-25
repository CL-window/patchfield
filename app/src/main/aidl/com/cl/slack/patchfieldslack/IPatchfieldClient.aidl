// IPatchfieldClient.aidl
package com.cl.slack.patchfieldslack;

// Declare any non-default types here with import statements

interface IPatchfieldClient {

      void onModuleCreated(String name, int inputChannels, int outputChannels, in Notification notification);
      void onModuleDeleted(String name);

      void onModuleActivated(String name);
      void onModuleDeactivated(String name);

      void onPortsConnected(String source, int sourcePort, String sink, int sinkPort);
      void onPortsDisconnected(String source, int sourcePort, String sink, int sinkPort);

      void onStart();
      void onStop();
}
