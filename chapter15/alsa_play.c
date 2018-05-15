/* alsa_play.c
 */

#include <alsa/asoundlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
    short buffer[4096];
    int err;
    unsigned int fs = 16000;
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;
    unsigned long ptr = 0, i;

    err = snd_pcm_open(&handle, "plughw:1,0", SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        perror("Device open error.\n");
        return -1;
    }

    err = snd_pcm_set_params(handle,
                             SND_PCM_FORMAT_S16_LE,
                             SND_PCM_ACCESS_RW_INTERLEAVED,
                             2,         /* 通道数 */
                             fs,        /* 采样率 */
                             1,         /* 重采样 */
                             100000     /* 延迟(us) */
                            );
    if (err < 0) {
        perror("Playback open error.\n");
        return -1;
    }

    while (1) {
        for(i = 0; i < 4096; i += 2) {
            buffer[i + 0] = 20000*sin(2*M_PI*ptr*500/fs);  /* 500Hz */
            buffer[i + 1] = 20000*sin(2*M_PI*ptr*800/fs);  /* 800Hz */
            ptr++;
        }
        err = snd_pcm_wait(handle, 1000);
        if (err < 0) {
            fprintf (stderr, "poll failed (%d)\n", err);
            break;
        }

        frames = snd_pcm_writei(handle, buffer, 2048);

        if (frames < 0)
            err = snd_pcm_recover(handle, frames, 0);
        if (err < 0) {
            perror("snd_pcm_writei failed.\n");
            break;
        }
    }
    snd_pcm_close(handle);  

    return 0;
}
