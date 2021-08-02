# -*- coding: utf-8 -*

# 测试，用麦克风录制语音输入，通过模型进行预测结果
# 录制音频-因为模型没有识别silence的功能，所以需要采用具有vad检测功能的录制工具，此处采用speech recognition
# !pip install SpeechRecognition
import pathlib
import keras
import numpy as np
import tensorflow as tf
import sklearn
from keras.models import load_model
from sklearn import preprocessing
import speech_recognition as sr
import os
# import scipy
# from scipy import io
from scipy import signal
from scipy.io import wavfile
# import matplotlib.pyplot as plt
from IPython.display import clear_output
#import h5py


# 载入模型
# model = load_model("mymodel.hdf5")

model = load_model("lstm.h5")

commands = ["backward","forward","go", "left","off", "on", "right", "stop"]

# 将命令转换为数字
le = sklearn.preprocessing.LabelEncoder()
le.fit_transform(commands)


# 计算时频谱
def log_specgram(audio, sample_rate, window_size=20,
                 step_size=10, eps=1e-10):
    nperseg = int(round(window_size * sample_rate / 1e3))
    noverlap = int(round(step_size * sample_rate / 1e3))
    freqs, times, spec = signal.spectrogram(audio,
                                    fs=sample_rate,
                                    window='hann',
                                    nperseg=nperseg,
                                    noverlap=noverlap,
                                    detrend=False)
    return freqs, times, np.log(spec.T.astype(np.float32) + eps)

# 输入文件的路径返回MFCC
def get_specgram(file_path):
    sample_rate, signal = wavfile.read(file_path)
    # 统一输入音频文件长度，当音频文件大于1秒时截尾，当音频文件小于1秒时补零
    signal_padding = np.zeros((16000,))
    if len(signal) >= 16000:
        signal_padding = signal[:16000]
    else:
        signal_padding[:len(signal)] = signal
    # 获取频道
    _, _, specgram = log_specgram(signal_padding, sample_rate=16000)
    # specgram = np.expand_dims(np.array(specgram),axis=-1)
    # print(specgram.shape)

    return specgram


# obtain audio from the microphone

r = sr.Recognizer()
with sr.Microphone(device_index=2, sample_rate=16000) as source:
    while True:
        r.adjust_for_ambient_noise(source)
        if r.energy_threshold < 400:
            r.energy_threshold = 400
        print(r.energy_threshold)
        print("say something!",commands)
        print()
        audio = r.listen(source)

        # write audio to a WAV file
        with open("microphone.wav","wb") as f:
            f.write(audio.get_wav_data())

        if os.path.isfile("microphone.wav"):
            input_data = get_specgram("microphone.wav").reshape(-1,99,161)
            result = model.predict(input_data)
            y_pred = np.argmax(result)
            
            label = le.inverse_transform(y_pred.reshape(1))

            print("识别结果：",label)
            with open("/tmp/output","w") as file:
                file.write(label[0])
            #print(le.inverse_transform(y_pred.reshape(1)))
            data = result.reshape(len(commands))
            clear_output(wait=True)
            # fig = plt.figure()
            # plt.bar(commands,np.array(data))
            # plt.show()
            os.remove("microphone.wav")
        else:
            print("file not exist")
