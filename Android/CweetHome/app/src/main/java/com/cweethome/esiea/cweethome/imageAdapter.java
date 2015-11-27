package com.cweethome.esiea.cweethome;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;

/**
 * Created by a190239 on 26/11/2015.
 */

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;

public class imageAdapter extends BaseAdapter {
    private Context mContext;

    // Constructor
    public imageAdapter(Context c){
        mContext = c;
    }

    public int getCount() {
        return mThumbIds.length;
    }

    public Object getItem(int position) {
        return null;
    }

    public long getItemId(int position) {
        return 0;
    }


    public View getView(int position, View convertView, ViewGroup parent) {

        ImageView imageView;

        if(convertView == null) {
            imageView = new ImageView(mContext);
            imageView.setLayoutParams(new GridView.LayoutParams(330, 330));
            imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
            imageView.setPadding(8, 8, 8, 8);
        } else {
            imageView = (ImageView) convertView;
        }

        imageView.setImageResource(mThumbIds[position]);
        return imageView;
    }

    // Keep all Images in array
    private Integer[] mThumbIds = {
            R.drawable.gate_open,
            R.drawable.door_open,
            R.drawable.garage_open,
            R.drawable.wicket_open,
            R.drawable.home_unlock,
            R.drawable.light_on_option,
            R.drawable.shutters_open_option,
            R.drawable.temperature_optin,
            R.drawable.informations_option,
            R.drawable.settings
    };
}
