/*
 * Copyright 2013 Google Inc. All Rights Reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */

package com.cl.slack.patchfieldslack.patchfield;

import android.app.Activity;
import android.app.Notification;
import android.app.PendingIntent.CanceledException;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.KeyEvent;

import com.cl.slack.patchfieldslack.IPatchfieldService;
import com.cl.slack.patchfieldslack.service.PatchfieldService;

import java.util.List;

/**
 * This convenience class encapsulates two common features of activities that use Patchfield, the
 * connection to the Patchfield service and navigation to a control activity via a long press on
 * the back button.
 */
public abstract class PatchfieldActivity extends Activity {

    protected IPatchfieldService patchfield = null;

    private ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.i("slack", "onServiceDisconnected...");
            patchfield = null;
            onPatchfieldDisconnected();
        }

        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Log.i("slack", "onServiceConnected...");
            patchfield = IPatchfieldService.Stub.asInterface(service);
            onPatchfieldConnected();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // 依旧 隐式 调用
//        bindService(createExplicitFromImplicitIntent(this, new Intent("IPatchfieldService")), connection, Context.BIND_AUTO_CREATE);
        // 显示调用
        bindService(new Intent(this, PatchfieldService.class), connection, Context.BIND_AUTO_CREATE);
    }

    /***
     * Android L (lollipop, API 21) introduced a new problem when trying to invoke implicit intent,
     * "java.lang.IllegalArgumentException: Service Intent must be explicit"
     *
     * If you are using an implicit intent, and know only 1 target would answer this intent,
     * This method will help you turn the implicit intent into the explicit form.
     *
     * Inspired from SO answer: http://stackoverflow.com/a/26318757/1446466
     * @param context
     * @param implicitIntent - The original implicit intent
     * @return Explicit Intent created from the implicit original intent
     */
    public Intent createExplicitFromImplicitIntent(Context context, Intent implicitIntent) {
        // Retrieve all services that can match the given intent
        PackageManager pm = context.getPackageManager();
        List<ResolveInfo> resolveInfo = pm.queryIntentServices(implicitIntent, 0);

        // Make sure only one match was found
        if (resolveInfo == null || resolveInfo.size() != 1) {
            return null;
        }

        // Get component info and create ComponentName
        ResolveInfo serviceInfo = resolveInfo.get(0);
        String packageName = serviceInfo.serviceInfo.packageName;
        String className = serviceInfo.serviceInfo.name;
        ComponentName component = new ComponentName(packageName, className);

        // Create a new intent. Use the old one for extras and such reuse
        Intent explicitIntent = new Intent(implicitIntent);

        // Set the component to be explicit
        explicitIntent.setComponent(component);

        return explicitIntent;
    }

    protected abstract void onPatchfieldConnected();

    protected abstract void onPatchfieldDisconnected();

    /**
     * When overriding the onDestroy method, make sure to invoke this parent method _at the end_.
     */
    @Override
    protected void onDestroy() {
        unbindService(connection);
        patchfield = null;
        super.onDestroy();
    }

    @Override
    public boolean onKeyLongPress(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK && patchfield != null) {
            try {
                Notification notification = patchfield.getNotification(null);
                if (notification != null) {
                    notification.contentIntent.send();
                    return true;
                }
            } catch (RemoteException | CanceledException e) {
                // Do nothing.
            }
        }
        return super.onKeyLongPress(keyCode, event);
    }
}
