import wave
import numpy as np

def wav_to_txt(wav_file, output_txt_file):
    # Abre o arquivo .wav
    with wave.open(wav_file, 'rb') as wav:
        # Obtém os parâmetros do arquivo .wav
        n_channels = wav.getnchannels()
        sampwidth = wav.getsampwidth()
        framerate = wav.getframerate()
        n_frames = wav.getnframes()
        
        # Lê os frames do arquivo .wav
        frames = wav.readframes(n_frames)
        
        # Converte os frames para um array numpy
        dtype = np.int16 if sampwidth == 2 else np.int8
        audio_array = np.frombuffer(frames, dtype=dtype)
        
        # Se o áudio for estéreo, converte para mono
        if n_channels == 2:
            audio_array = audio_array.reshape(-1, 2).mean(axis=1)
        
        # Normaliza os valores para 8 bits (0 a 255) sem distorção
        max_abs_value = np.max(np.abs(audio_array))  # Valor máximo absoluto
        if max_abs_value > 0:  # Evita divisão por zero
            audio_array = (audio_array / max_abs_value) * 127 + 128  # Centraliza em 128
            audio_array = np.clip(audio_array, 0, 255).astype(np.uint8)  # Limita ao intervalo 0-255
        
        # Gera o arquivo .txt com os valores
        with open(output_txt_file, 'w') as txt_file:
            for i in range(0, len(audio_array), 10):
                line = audio_array[i:i+10]
                txt_file.write(", ".join(map(str, line)) + ",\n")
    
    print(f"Arquivo .txt gerado: {output_txt_file}")

# Exemplo de uso
wav_file = 'audio.wav'
output_txt_file = 'audio_data.txt'
wav_to_txt(wav_file, output_txt_file)