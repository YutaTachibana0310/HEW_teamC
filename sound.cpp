#include "main.h"
#include "sound.h"

// ���܂��Ȃ�
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

// �O���[�o���ϐ�
IDirectSound8 *g_pDirectSound = NULL;	// �T�E���h�C���^�[�t�F�[�X

// �T�E���h�̏�����
// hWnd:�E�B���h�E�n���h��
HRESULT InitSound( HWND hWnd )
{
	// DirectSound�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound, NULL)))
		return E_FAIL;
	
	// �������x���ݒ� 
	if (FAILED(g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;

	return S_OK;
}

// ��Еt��
void UninitSound()
{	
	if( g_pDirectSound != NULL )
	{
		g_pDirectSound->Release();
		g_pDirectSound = NULL;
	}
}

// �T�E���h�̃��[�h
// no:�T�E���h�i���o�[�i�w�b�_�ɒ�`���ꂽ�񋓌^�萔�j
LPDIRECTSOUNDBUFFER8 LoadSound(const TCHAR *path )
{
	// MMIO = �}���`���f�B�A���o�́A�̗��B
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// �ȃf�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// �ȃf�[�^�̃o�b�t�@
	DSBUFFERDESC buff;						// �o�b�t�@�ݒ�\����

	HMMIO hMmio = NULL;						// MMIO�n���h��
	MMIOINFO mmioInfo;						// �}���`���f�B�A�f�[�^�\����

	MMRESULT mmRes;								// MM�������ʊi�[�ϐ�
	MMCKINFO riffChunk, formatChunk, dataChunk;	// �`�����N�f�[�^�\����
	DWORD size;									// �f�[�^�T�C�Y�i�[�p
	WAVEFORMATEX pcm;							// �ȃf�[�^�t�H�[�}�b�g�\����

	LPVOID pBlock;				// �Z�J���_���o�b�t�@�̃f�[�^�������ݐ�A�h���X
	DWORD  dwSize;				// �Z�J���_���o�b�t�@�̃T�C�Y

	// 1.�n���h�������ƂɃt�@�C�����J��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)path, &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// 2.�t�@�C����͇@ RIFF�`�����N����
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3.�t�@�C����͇A �t�H�[�}�b�g�`�����N����
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);	// �����������Ƃɓǂݍ���
	
	if(size != formatChunk.cksize) 		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0); 

	// 4.�t�@�C����͇B �f�[�^�`�����N����
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR) 		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 5.�f�[�^�ǂݍ���
	char *pData = new char[dataChunk.cksize];					// �K�v�ȑ傫���̗̈���m�ۂ���
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// �f�[�^��ǂݍ���
	
	if(size != dataChunk.cksize)  		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		delete[] pData;
		return NULL;
	}

	// 6.�Ȃ�ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));		// �܂�������
	buff.dwSize = sizeof(DSBUFFERDESC);			// ��������e��ݒ�
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// �����o�b�t�@�����
	if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
		return NULL;

	// �T�E���h�o�b�t�@�����o��
	if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
		return NULL;

	// ���o�����瑍���o�b�t�@���̂Ă�
	pBaseBuffer->Release();

	// 7.���ꂽ�Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// �܂��͏������݂ł���悤�o�b�t�@�����b�N
	if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);	// �f�[�^�]��
	delete[] pData;					// ���̓ǂݍ��ݗ̈������

	// �o�b�t�@���b�N����
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// �Z�J���_���o�b�t�@��Ԃ��Ă悤�₭����...
	return pBuffer;
}

// ����炷
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
// flag   :1(E_DS8_FLAG_LOOP)�Ȃ烋�[�v�Đ�
void PlaySoundBuffer(  LPDIRECTSOUNDBUFFER8 pBuffer, int flag, bool fromHead)
{
	if (pBuffer == NULL)
	{
		return;
	}

	if (fromHead)
	{	// ��������炷�̂ŁA�ŏ�����炵�����ꍇ��SetCurrentPosition(0)�����邱��
		pBuffer->SetCurrentPosition(0);
	}

	pBuffer->Play(0, 0, flag);
}

// �����~�߂�
void StopSoundBuffer( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	if (pBuffer == NULL)
	{
		return;
	}

	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )	// ���Ă�����
	{
		pBuffer->Stop();	// �Ӗ��I�ɂ�Pause�ɂȂ�B
	}
}

// �Đ������ǂ������ׂ�
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
bool IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	if (pBuffer == NULL)
	{
		return false;
	}

	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )
	{
		return true;
	}
	return false;
}

//�{�����[���̐ݒ�(volume:100 �` 0[%])
void SetSoundVolume(LPDIRECTSOUNDBUFFER8 pBuffer, float volume)
{
	if (pBuffer == NULL)
	{
		return;
	}

	//�{�����[���̒P�ʂ��f�V�x���ɕϊ�
	LONG decibel = (LONG)(2000.0f * log10(volume / 100.0f));
	
	if (decibel < DSBVOLUME_MIN)
	{
		decibel = DSBVOLUME_MIN;
	}
	else if (decibel > DSBVOLUME_MAX)
	{
		decibel = DSBVOLUME_MAX;
	}

	pBuffer->SetVolume(decibel);
}
