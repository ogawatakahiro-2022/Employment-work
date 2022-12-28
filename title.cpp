//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ����@�Y��
//
//=============================================================================
#include "title.h"
#include "Input.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(SCREEN_WIDTH)	// �w�i�T�C�Y
#define TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 
#define TEXTURE_MAX					(5)				// �e�N�X�`���̐�

#define TEXTURE_WIDTH_LOGO			(480)			// ���S�T�C�Y
#define TEXTURE_HEIGHT_LOGO			(80)			// 

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/bg000.jpg",
	"data/TEXTURE/title.png",
	"data/TEXTURE/tex.png",
	"data/TEXTURE/OT1G_01.png"
	"data/TEXTURE/title_logo.png"
};



static BOOL		g_Load = FALSE;
static TITLE	g_Title;

static float	alpha;
static BOOL		flag_alpha;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// �ϐ��̏�����
	g_Title.w     = TEXTURE_WIDTH;
	g_Title.h     = TEXTURE_HEIGHT;
	g_Title.pos   = XMFLOAT3(g_Title.w /2, g_Title.h /2, 0.0f);
	g_Title.texNo = 0;

	alpha = 1.0f;
	flag_alpha = TRUE;


	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	if (g_Load == FALSE) return;

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{//Enter��������A�X�e�[�W��؂�ւ���
		//SetMode(MODE_GAME);
		SetFade(FADE_OUT, MODE_TUTORIAL);
	}
	//�Q�[���p�b�h�œ��͏���
	else if (IsButtonTriggered(0, BUTTON_START))
	{
		//SetMode(MODE_GAME);
		SetFade(FADE_OUT, MODE_TUTORIAL);

	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		//SetMode(MODE_GAME);
		SetFade(FADE_OUT, MODE_TUTORIAL);

	}
#ifdef _DEBUG	// �f�o�b�O����\������
	//PrintDebugProc("Player:�� �� �� ���@Space\n");

#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();		//2D�\�����s���ݒ�

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�		���_�P�ʂł͂Ȃ��ATEX���̂��̂ɃG�t�F�N�g���s��
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));

	//�ގ�(TEX)�̐F�����̂܂܎g���ݒ�
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// �^�C�g���̔w�i��`��
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		float px = 0.0f;			// ���_���W
		float py = 0.0f;
		float pw = TEXTURE_WIDTH;
		float ph = TEXTURE_HEIGHT;

		float tx = 0.0f;			// Tex���W
		float ty = 0.0f;
		float tw = 1.0f;
		float th = 1.0f;

		// �|���S���쐬
		SetSpriteLeftTop(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);		//4���_�@0�Ԗڂ���`��Ƃ����ݒ�
	}


}





