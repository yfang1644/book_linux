/* alsa_record.c
 */

#include <alsa/asoundlib.h>
#include <unistd.h>
#include <stdio.h>

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
                             1,         /* 通道数 */
                             fs,        /* 采样率 */
                             1,         /* 重采样 */
                             100000     /* 延迟(us) */
                            );
    if (err < 0) {
        perror("Playback open error.\n");
        return -1;
    }

    while (1) {
        frames = snd_pcm_readi(handle, buffer, 4096);
        if (frames == -EPIPE) {
            /*  EPIPE means overrun */
            fprintf(stderr, "overrun occurred\n");
            snd_pcm_prepare(handle);
        } else if (frames < 0) {
            fprintf(stderr, "error from read.\n");
        } else if (4096 != (int)frames) {
            fprintf(stderr, "read %ld, expected 4096.\n", frames);
        }

        err = write(STDOUT_FILENO, buffer, sizeof(buffer));
    }
    snd_pcm_close(handle);  

    return 0;
}
