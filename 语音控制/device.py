import speech_recognition as sr
import pyaudio

p = pyaudio.PyAudio()
for i in range(p.get_device_count()):
        info = p.get_device_info_by_index(i)
        print(info['index'], info['name'])

r=sr.Recognizer()
#print(sr.Microphone.list_working_microphones())

