//===========================================
// Copyright (C) 2013 Cedric Liaudet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to
// do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//===========================================
#include "SamRendererPCH.h"
#include "renderer/CMaterialManager.h"
#include "renderer/CRenderWindow.h"
#include "renderer/CMaterial.h"
#include "renderer/CPixelShader.h"
#include "renderer/CVertexShader.h"

namespace sam
{
    //***************//
    // HELPER METHODS//
    //***************//    
    // Remove carriage return from the string.
    uint32 RemoveCarriageReturn(char *_pStr)
    {
        uint32 nNbChar = 0;
        while(*_pStr && (*_pStr == '\r' || *_pStr == '\n')) 
        {
            ++nNbChar;
            ++_pStr;
        }

        return nNbChar;
    }

    static char *g_pShaderVertexModel[] = {
        "vs_2_0",
        "vs_3_0",
        "vs_4_0",
        "vs_5_0",
        NULL
    };

    static char *g_pShaderPixelModel[] = {
        "ps_2_0",
        "ps_3_0",
        "ps_4_0",
        "ps_5_0",
        NULL
    };

    struct SRenderStateParams
    {
        char *m_sName;
        uint32 m_nLength;
        CMaterial::EFunctionID m_eFuncID;
    };    

    /// @brief Default constructor.
    CMaterialManager::CMaterialManager(void)
        : m_pFirstMaterial(NULL), m_pLastMaterial(NULL)
    {

    }

    // Load material from stream.
    CMaterial *CMaterialManager::CreateMaterial(IStream *p_pStream, const char *p_sName)
    {
        SAM_ASSERT(p_pStream != NULL, "p_pStream is null");

		/*
		technique "__name__"
		{
			pass "__name__"
			{
				vertex "__storage:name.function__"
				pixel "__storage:name.function__"

				render_state value

				texture
				{
				}
			}
		}
		*/

        enum EParseState
        {
            PS_Technique,
            PS_Pass,
            PS_VertexProgram,
            PS_PixelProgram,
            PS_Parameter,
            PS_RenderState,
            PS_TextureUnit,
            PS_Bracket,
        }eParseState = PS_Technique;

        // List of available parameters.
        SRenderStateParams aRenderStateParams[] =
        {
            {"blend_factor", 12, CMaterial::FID_BLEND_FACTOR},
            {"blend_color", 11, CMaterial::FID_BLEND_COLOR},
            {"blend_op", 8, CMaterial::FID_BLEND_OP},
            {"fill_mode", 9, CMaterial::FID_Unknown},
            {NULL, 0}
        };
        
        // load stream.
        uint32 nLength = p_pStream->Size();
        char *pBuffer = (char*)p_pStream->Data();

        CMaterial *pMaterial = NULL;
        
        
        char *pShaderBuffer = pBuffer;

        uint32 nNbBracket = 0;
        uint32 nStartPosition = 0;
        char pLine[256] = {'\0'};
        while(pShaderBuffer[0] != '\0')
        {
            // get line.
            uint32 nEndOfLine = strcspn(pShaderBuffer, "\n\r\0");             

            /* error */
            if(nEndOfLine == nLength)
            {
                SamLogWarning("Unable to parse the material file '%s'", p_sName);
                break;
            }

            /* copy */
            nStartPosition = 0;
            strncpy(pLine, pShaderBuffer, nEndOfLine);
            pLine[nEndOfLine] = '\0';

            /* remove blank */            
            nStartPosition += RemoveWhiteSpace(pLine);

            // update the position.
            nLength -= nEndOfLine;
            pShaderBuffer += nEndOfLine;

            // check if line is not empty.
            if(nStartPosition < nEndOfLine)
            {
                switch(eParseState)
                {
                case PS_Technique:
                    {
                        if(strncmp(&pLine[nStartPosition], "technique", 9) != 0)
                        {
                            SamLogError("Malformed material file '%s'", p_sName);
                            break;
                        }

                        // update the position.
                        nStartPosition += 9;

                        /* remove blank */
                        nStartPosition += RemoveWhiteSpace(&pLine[nStartPosition]);

                        // retrieves the name of the technique.
                        uint32 nEndOfWord = strcspn(&pLine[nStartPosition], " \n\r");

                        pMaterial = SAM_NEW CMaterial(CreateID(&pLine[nStartPosition], nEndOfWord));

                        eParseState = PS_Bracket;
                    }                
                    break;

                case PS_Bracket:
                    {
                        if(pLine[nStartPosition] != '{')
                        {
                            SamLogError("Malformed material file '%s'", pMaterial->GetID());
                            break;
                        }

                        if(!nNbBracket)
						{
                            eParseState = PS_Pass;
						}
                        else if(nNbBracket == 1)
						{
                            eParseState =  PS_VertexProgram;
						}
                        else if(nNbBracket == 2)
						{
                            eParseState = PS_TextureUnit;
						}
                        else
                        {
                            SamLogError("Malformed material file '%s'", p_sName);
                            break;
                        }

                        ++nNbBracket;
                    }                
                    break;

                case PS_Pass:
                    {
                        // check if we are at the end.
                        if(pLine[nStartPosition] == '}')
                        {
                            --nNbBracket;
                            break;
                        }

                        if(strncmp(&pLine[nStartPosition], "pass", 4) != 0)
                        {
                            SamLogError("Malformed material file '%s'", p_sName);
                            break;
                        }

                        // update the position.
                        nStartPosition += 4;

                        /* remove blank */
                        nStartPosition += RemoveWhiteSpace(&pLine[nStartPosition]);

                        // retrieves the name of the pass.
                        uint32 nEndOfWord = strcspn(&pLine[nStartPosition], " \n\r");

                        printf("Pass Name %s\n", &pLine[nStartPosition]);
                        eParseState = PS_Bracket;
                    }
                    break;
					
                case PS_VertexProgram:
                    {
                        if(strncmp(&pLine[nStartPosition], "vertex", 6) != 0)
                        {
                            SamLogError("Malformed material file '%s'", p_sName);
                            break;
                        }

                        // update position
                        nStartPosition += 6;

                        /* remove blank */
                        nStartPosition += RemoveWhiteSpace(&pLine[nStartPosition]);

                        // get profile.
                        uint16 nIndex = 0;
                        while(g_pShaderVertexModel[nIndex])
                        {
                            if(strncmp(&pLine[nStartPosition], g_pShaderVertexModel[nIndex], 6) == 0)
                                break;

                            ++nIndex;
                        }

                        if(g_pShaderVertexModel[nIndex] == NULL)
                        {
                            SamLogError("Malformed material file '%s'", p_sName);
                            break;
                        }

                        // update the position.
                        nStartPosition += 6;

                        /* remove blank */
                        nStartPosition += RemoveWhiteSpace(&pLine[nStartPosition]);

						// retrieves storage name.
						uint32 nEndOfWord = strcspn(&pLine[nStartPosition], ":");
						char sStorageName[64];
						memset(sStorageName, '\0', 64);
						strncpy(sStorageName, &pLine[nStartPosition], nEndOfWord);
						nStartPosition += nEndOfWord + 1;

                        // retrieves file and method name.						
                        char sProgramFileName[256];
						memset(sProgramFileName, '\0', 256);
                        strncpy(sProgramFileName, &pLine[nStartPosition], nEndOfWord);
                        sProgramFileName[nEndOfWord] = '.';
                        sProgramFileName[nEndOfWord + 1] = 'v';
                        sProgramFileName[nEndOfWord + 2] = 's';

						uint32 nEndStorageName = strcspn(&pLine[nStartPosition], ":");

                        // Get/Create vertex shader.
						ID nID = CreateID(sProgramFileName, nEndOfWord);
                        CVertexShader *pVertexShader = (CVertexShader*)g_Env->pRenderWindow->GetVertexShader(nID);
                        if(!pVertexShader)
                        {
                            nStartPosition += nEndOfWord + 1;
                            nEndOfWord = strcspn(&pLine[nStartPosition], " \n\r");
                            char sMethod[256] = {'\0'};
                            strncpy(sMethod, &pLine[nStartPosition], nEndOfWord);

							IStream *pStream = g_Env->pResourceStorageManager->GetResource(sProgramFileName, sStorageName);
							if(pStream != NULL)
							{
								pVertexShader = (CVertexShader*)g_Env->pRenderWindow->CreateVertexShader(pStream, nID, sMethod, g_pShaderVertexModel[nIndex]);
								pMaterial->SetVertexShader(pVertexShader);
							}
                        }
                        
                        eParseState = PS_PixelProgram;
                    }
                    break;

                case PS_PixelProgram:
                    {
                        if(strncmp(&pLine[nStartPosition], "pixel", 5) != 0)
                        {
                            SamLogError("Malformed material file '%s'", p_sName);
                            break;
                        }

                        // update position
                        nStartPosition += 5;

                        /* remove blank */
                        nStartPosition += RemoveWhiteSpace(&pLine[nStartPosition]);

                        // get profile.
                        uint16 nIndex = 0;
                        while(g_pShaderPixelModel[nIndex])
                        {
                            if(strncmp(&pLine[nStartPosition], g_pShaderPixelModel[nIndex], 6) == 0)
                                break;

                            ++nIndex;
                        }

                        if(g_pShaderPixelModel[nIndex] == NULL)
                        {
                            SamLogError("Malformed material file '%s'", p_sName);
                            break;
                        }

                        // update the position.
                        nStartPosition += 6;

                        /* remove blank */
                        nStartPosition += RemoveWhiteSpace(&pLine[nStartPosition]);

						// retrieves storage name.
						uint32 nEndOfWord = strcspn(&pLine[nStartPosition], ":");
						char sStorageName[64];
						memset(sStorageName, '\0', 64);
						strncpy(sStorageName, &pLine[nStartPosition], nEndOfWord);
						nStartPosition += nEndOfWord + 1;

                        // retrieves file and method name.
                        nEndOfWord = strcspn(&pLine[nStartPosition], ".");
                        char sProgramFileName[256] = {'\0'};
                        strncpy(sProgramFileName, &pLine[nStartPosition], nEndOfWord);
                        sProgramFileName[nEndOfWord] = '.';
                        sProgramFileName[nEndOfWord + 1] = 'p';
                        sProgramFileName[nEndOfWord + 2] = 's';                        

                        // Get/Create pixel shader.
						ID nID = CreateID(sProgramFileName, nEndOfWord);
                        CPixelShader *pPixelShader = g_Env->pRenderWindow->GetPixelShader(nID);
                        if(!pPixelShader)
                        {
                            nStartPosition += nEndOfWord + 1;
                            nEndOfWord = strcspn(&pLine[nStartPosition], " \n\r");
                            char sMethod[256] = {'\0'};
                            strncpy(sMethod, &pLine[nStartPosition], nEndOfWord);

							IStream *pStream = g_Env->pResourceStorageManager->GetResource(sProgramFileName, sStorageName);
							if(pStream != NULL)
							{
								pPixelShader = g_Env->pRenderWindow->CreatePixelShader(pStream, nID, sMethod, g_pShaderPixelModel[nIndex]);
								pMaterial->SetPixelShader(pPixelShader);
							}
                        }

                        eParseState = PS_RenderState;
                    }
                    break;

                case PS_RenderState:
                    {
                        // check if we are at the end.
                        if(pLine[nStartPosition] == '}')
                        {
                            --nNbBracket;
                            eParseState = PS_Pass;
                            break;
                        }
                        else if(strncmp(&pLine[nStartPosition], "texture", 7) == 0)
                        {
                            eParseState = PS_Bracket;
                            break;
                        }

                        // find parameter.
                        uint16 nIndex = 0;
                        while(aRenderStateParams[nIndex].m_sName)
                        {
                            if(strncmp(&pLine[nStartPosition], aRenderStateParams[nIndex].m_sName, aRenderStateParams[nIndex].m_nLength) == 0)
                                break;

                            ++nIndex;
                        }

                        if(aRenderStateParams[nIndex].m_sName == NULL)
                        {
                            SamLogError("Malformed material file '%s'", p_sName);
                            break;
                        }

                        if(aRenderStateParams[nIndex].m_eFuncID == CMaterial::FID_Unknown)
                        {
                            SamLogError("Parameter '%s' is already setted in material file '%s'", aRenderStateParams[nIndex].m_sName, p_sName);
                            break;
                        }

                        // update the position.
                        nStartPosition += aRenderStateParams[nIndex].m_nLength;

                        /* remove blank */
                        nStartPosition += RemoveWhiteSpace(&pLine[nStartPosition]);

                        // retrieves parameter(s).
                        pMaterial->AddParam(aRenderStateParams[nIndex].m_eFuncID, &pLine[nStartPosition]);

                        // Invalidate param.
                        aRenderStateParams[nIndex].m_eFuncID = CMaterial::FID_Unknown;
                    }
                    break;

                case PS_TextureUnit:
                    {
                        // TODO.
                        SamLog("TODO: Texture Unit parsing.");
                    }
                    break;
                }
            }

            // remove carriage return.
            uint32 nNbCR = RemoveCarriageReturn(pShaderBuffer);
            nLength -= nNbCR;
            pShaderBuffer += nNbCR;
        }

        if(pMaterial)
        {
            if(m_pLastMaterial)
                m_pLastMaterial->SetNext(pMaterial);
            else
                m_pFirstMaterial = pMaterial;

            m_pLastMaterial = pMaterial;
        }

        return pMaterial;
    }



    // Retrieves material from its ID.
    CMaterial *CMaterialManager::GetMaterial(const ID &p_nID) const
    {
        CMaterial *pMaterial = m_pFirstMaterial;
        while(pMaterial)
        {
            if(pMaterial->GetID() == p_nID)
                return pMaterial;

            pMaterial = pMaterial->GetNext();
        }

        return NULL;
    }

    // Retrieves material from its name.
    CMaterial *CMaterialManager::GetMaterial(const char *p_sName) const
    {
        return GetMaterial(CreateID(p_sName, strlen(p_sName)));
    }
}
