__author__ = 'fpbatta'

__doc__ = """
simple data extractor for testing the plugins
"""

import sys
import h5py
import math
import numpy as np
import matplotlib.pyplot as plt
import time
plt.switch_backend('QT4Agg')


plt.ion()
pluginDir = "/Users/fpbatta/src/GUImerge/GUI/Plugins"
testDataFile = "/Users/fpbatta/dataLisa/disruption0902/100_raw_test.kwd"
sys.path.append(pluginDir)

import SPWfinder.plugin

plugin = SPWfinder.plugin.SPWFinder()
tFile = h5py.File(testDataFile)
tData = tFile["/recordings/0/data"]
sample_rate = tFile["/recordings/0"].attrs["sample_rate"][0]
bit_volts = tFile["/recordings/0/application_data"].attrs["channel_bit_volts"]

samples_in_441k_rate = 1024

samples_per_frame = int(samples_in_441k_rate * sample_rate / 44100.)

print "tData: ", tData
print "sample_rate: ", sample_rate

plugin.startup(sample_rate)
def reload_plugin():
    reload(SPWfinder.plugin)
    plugin = SPWfinder.plugin.SPWFinder()


def lookup_data(tStart, tEnd):
    iStart = int(tStart * sample_rate)
    print "iStart: ", iStart
    iEnd = int(tEnd * sample_rate)
    iD = iEnd - iStart
    iD = samples_per_frame * math.floor(iD/samples_per_frame)
    iEnd = int(iStart + iD)

    print "iEnd: ", iEnd

    data = tData[iStart:iEnd, :] * bit_volts
    spread = 300
    nSamples = data.shape[0]
    nChans = data.shape[1]
    print nSamples

    plugin.chan_in = 18-1
    plugin.threshold = 10
    chans_to_plot = [1, 2, 3, 4, 5, plugin.chan_in+1]

    print "chan_in: ", plugin.chan_in
    frame_starts = np.arange(iStart, iEnd, samples_per_frame, dtype=np.int)
    data = np.zeros([0,nChans], dtype=np.float32)
    t = 0.
    event_time = tStart
    frame_duration = float(samples_per_frame) / sample_rate
    print "frame duration: ", frame_duration
    event_times = np.empty([0,], dtype=np.float64)
    means = np.empty([0,], dtype=np.float64)
    do_overall_plot = False
    do_buffer_plots = False
    if do_buffer_plots:
        fig = plt.figure(2)
        ax = fig.add_subplot(111)

        (hlg,) = ax.plot([],[])
        (hls,) = ax.plot([], [])
        plt.show(block=False)
        plt.waitforbuttonpress()
        print 'ready'
    for ix in frame_starts: # frame_starts:
        d = tData[ix:(ix+samples_per_frame), :].astype(np.float32)
        #d0 = d.copy()
        d *= 0.195
        (events, sig, filt, mean) = plugin.bufferfunction(d.transpose() )
        means = np.append(means, mean)
        data = np.concatenate((data, d), axis=0)
        event_time += frame_duration
        if events:
            for e in events:
                print e
                if e['eventId'] == 1:
                    event_times = np.append(event_times, event_time)


        if do_buffer_plots:
            hlg.set_xdata(np.arange(len(filt)))
            hlg.set_ydata(filt)
            hls.set_xdata(np.arange(len(filt)))
            hls.set_ydata(sig)
            ax.relim()
            ax.autoscale_view(True,True,True)
            # mng = plt.get_current_fig_manager()
            # mng.window.raise_()
            plt.draw()
            #plt.show(block=False)
            plt.waitforbuttonpress()
            print "done"
    t = np.linspace(tStart, tEnd, data.shape[0])
    print event_times

    if do_overall_plot:
        plt.figure(1)
        for ix, ch in enumerate(chans_to_plot):
            x = t
            y = data[:,ch-1]-ix*spread
            plt.plot(x, y)
            plt.text(tStart+(tEnd-tStart)*1., -ix*spread, str(ch))
        plt.plot(event_times, -3*spread * np.ones(event_times.shape), 'go')

        mng = plt.get_current_fig_manager()
        mng.window.raise_()
        plt.show(block=True)
        # plt.waitforbuttonpress()
        # raw_input("enter")
    print 'done'
    np.savetxt('/Users/fpbatta/tmp/means.txt', means)

if __name__ == '__main__':
    lookup_data(0, 1)









