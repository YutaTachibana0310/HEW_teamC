//=============================================================================
//
// ���C������ [main.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include <time.h>
#include "sceneManager.h"
#include "collider.h"
#include "sound.h"
#include "soundEffectManager.h"
#include "bgmManager.h"
#include "debugWindow.h"
#include "DebugTimer.h"
#include "postEffectManager.h"
#include "screenBG.h"
#include "GUIManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"CYBERIDE -�T�C�o���C�h-"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawDebugWindowMain(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D �I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
//static D3DXCOLOR backColor = D3DCOLOR_RGBA(0, 0, 0, 0);
static D3DXCOLOR backColor = D3DCOLOR_RGBA(0, 0, 0, 255);
int					g_nCountFPS;			// FPS�J�E���^
bool				g_bDispDebug = true;	// �f�o�b�O�\��ON/OFF
static bool flgPause = false;

//�X�N���[���S�̂𕢂��e�N�X�`��
static LPDIRECT3DTEXTURE9 fullScreenTexture[2];
static LPDIRECT3DSURFACE9 fullScreenSurface[2];

//���݂̃V�[��
static int currentScene = 0;

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;
	MSG msg;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		0,//CW_USEDEFAULT,
		0,//CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	timeEndPeriod(1);				// ����\��߂�

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DebugWindPrcHandler(hWnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�pn
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W���Z��������
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));
	g_pD3DDevice->GetDeviceCaps(&caps);

#if 1
	if ((caps.RasterCaps & D3DPRASTERCAPS_FOGRANGE) != 0)
	{
		FLOAT StartPos = 2000;
		FLOAT EndPos = 10000;

		g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, backColor);
		g_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
		g_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
		g_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&StartPos));
		g_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&EndPos));
	}
#endif

	//�`��p�̃t���X�N���[���e�N�X�`�����쐬���T�[�t�F�C�X���擾
	for (int i = 0; i < 2; i++)
	{
		g_pD3DDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&fullScreenTexture[i],
			NULL);
		fullScreenTexture[i]->GetSurfaceLevel(0, &fullScreenSurface[i]);
	}

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	//�����蔻�菉����
	InitCollider(0);

	//�T�E���h�֘A������
	InitSound(hWnd);
	InitSoundEffectManager(0);
	InitBgmManager(0);

	//�X�N���[���w�i������
	InitScreenBG(0);
	
	//�|�X�g�G�t�F�N�g������
	InitPostEffectManager(0);

	//GUI�}�l�[�W��������
	//InitGUIManager(0);

	//�V�[���}�l�[�W��������
	InitSceneManager(&currentScene);

	//�f�o�b�O�E�B���h�E������
	InitDebugWindow(hWnd, g_pD3DDevice);

	SetScene((DefineScene)0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	SAFE_RELEASE(fullScreenSurface[0]);
	SAFE_RELEASE(fullScreenSurface[1]);
	SAFE_RELEASE(fullScreenTexture[0]);
	SAFE_RELEASE(fullScreenTexture[1]);

	// ���͏����̏I������
	UninitInput();

	//�V�[���}�l�[�W���I������
	UninitSceneManager(0);

	//�����蔻��I������
	UninitCollider(0);

	//�T�E���h�֘A�I������
	UninitSoundEffectManager(0);
	UninitBgmManager(0);
	UninitSound();

	//�f�o�b�O�^�C�}�[�I������
	UninitDebugTimer();

	//�X�N���[���w�i�I������1
	UninitScreenBG(0);

	//�|�X�g�G�t�F�N�g�I������
	UninitPostEffectManager(0);

	//GUI�}�l�[�W���I������
	UninitGUIManager(0);

#ifdef USE_DEBUGWINDOW
	UninitDebugWindow(0);
#endif
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͍X�V
	UpdateInput();

	UpdateDebugWindow();
	UpdateBgmManager();
	UpdateSoundEffectManager();

	UpdateCamera();
	UpdateLight();
	UpdateSceneManager();
	UpdatePostEffectManager();
	UpdateGUIManager();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	LPDIRECT3DSURFACE9 oldSurface = NULL;
	g_pD3DDevice->GetRenderTarget(0, &oldSurface);
	g_pD3DDevice->SetRenderTarget(0, fullScreenSurface[0]);
;	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), backColor, 1.0f, 0);
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawScreenBG();

		DrawSceneManager();

		DrawPostEffectManager(fullScreenTexture, fullScreenSurface, oldSurface);

		DrawGUIManager();

		DrawDebugWindow();

		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

/******************************************************************************
//�֐���	�FLPDIRECT3DTEXTURE9 CreateTextureFromFile(LPSTR szName, LPDIRECT3DDEVICE9 lpD3DDevice)
//����1		�FLPSTR szName�F�ǂݍ��݂����t�@�C����
//����2		�FLPDIRECT3DDEVICE9 lpD3DDevice�F�f�o�C�X�I�u�W�F�N�g
//�߂�l	�F�ǂݍ��񂾃e�N�X�`���ւ̃|�C���^
//����		�F�T�C�Y���w�肵�ăe�N�X�`���t�@�C����ǂݍ��ފ֐�
******************************************************************************/
LPDIRECT3DTEXTURE9 CreateTextureFromFile(LPSTR szName, LPDIRECT3DDEVICE9 lpD3DDevice)
{
	HRESULT             hRet;

	//�߂�l�̃e�N�X�`��
	LPDIRECT3DTEXTURE9  lpTex = NULL;
	if (lpD3DDevice) {

		//D3DXGetImageInfoFromFile�Ŏg�p����摜�t�@�C���̏��
		D3DXIMAGE_INFO      iinfo;

		//�摜�t�@�C���̏����擾
		hRet = D3DXGetImageInfoFromFile(szName, &iinfo);
		if (hRet == D3D_OK)
		{
			//�e�N�X�`�����t�@�C������쐬
			hRet = D3DXCreateTextureFromFileEx(
				lpD3DDevice,
				szName,
				iinfo.Width, iinfo.Height,			//�擾�����摜�t�@�C���̃T�C�Y���w�肷��
				1, 0,
				D3DFMT_A8R8G8B8,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_FILTER_NONE,
				0xFF000000,
				NULL, NULL,
				&lpTex);
		}
	}
	return lpTex;
}

//=============================================================================
// �r���[�|�[�g�ϊ�
//=============================================================================
void TranslateViewPort(D3DXVECTOR3 *out, D3DXVECTOR3 *pos)
{
	out->x = pos->x * (SCREEN_WIDTH / 2.0f) + SCREEN_WIDTH / 2.0f;
	out->y = pos->y * (-SCREEN_HEIGHT / 2.0f) + SCREEN_HEIGHT / 2.0f;
}

//=============================================================================
// �o�b�N�J���[�ύX
//=============================================================================
void SetBackColor(D3DXCOLOR color)
{
	backColor = color;
	g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, backColor);
}

//=============================================================================
// �f�o�b�O�E�B���h�E�\��
//=============================================================================
void DrawDebugWindowMain(void)
{
	BeginDebugWindow("Main");

	DebugText("FPS : %d", g_nCountFPS);

	EndDebugWindow("Main");
}

//=============================================================================
// �V�[���擾����
//=============================================================================
int GetCurrentScene(void)
{
	return currentScene;
}

//=============================================================================
// FPS�擾����
//=============================================================================
int GetCurrentFPS(void)
{
	return g_nCountFPS;
}