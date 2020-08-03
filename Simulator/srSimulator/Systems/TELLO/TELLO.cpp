#include "TELLO.h"

TELLO::TELLO():SystemGenerator()
{
  printf("[TELLO] ASSEMBLED\n");
}

TELLO::~TELLO(){
}

void TELLO::_SetJointLimit(){
}

void TELLO::_SetCollision(){
  collision_.resize(4);
  for (int i = 0; i < collision_.size(); ++i) {
    collision_[i] = new srCollision();
  }
  collision_[0]->GetGeomInfo().SetShape(srGeometryInfo::CAPSULE);
  collision_[0]->GetGeomInfo().SetDimension(0.05, 0.02, 0.0);
  collision_[0]->SetLocalFrame(EulerZYX(Vec3(0,0,M_PI/2.0), Vec3(0.07, 0, 0)));
 
  //collision_[1]->GetGeomInfo().SetShape(srGeometryInfo::SPHERE);
  collision_[1]->GetGeomInfo().SetShape(srGeometryInfo::CAPSULE);
  collision_[1]->GetGeomInfo().SetDimension(0.05, 0.02, 0.0);
  collision_[1]->SetLocalFrame(EulerZYX(Vec3(0,0,M_PI/2.0), Vec3(-0.06, 0, 0)));
  
  //collision_[2]->GetGeomInfo().SetShape(srGeometryInfo::SPHERE);
  collision_[2]->GetGeomInfo().SetShape(srGeometryInfo::CAPSULE);
  collision_[2]->GetGeomInfo().SetDimension(0.05, 0.02, 0.0);
  collision_[2]->SetLocalFrame(EulerZYX(Vec3(0,0,M_PI/2.0), Vec3(0.07, 0.0, 0)));

  //collision_[3]->GetGeomInfo().SetShape(srGeometryInfo::SPHERE);
  collision_[3]->GetGeomInfo().SetShape(srGeometryInfo::CAPSULE);
  collision_[3]->GetGeomInfo().SetDimension(0.05, 0.02, 0.0);
  collision_[3]->SetLocalFrame(EulerZYX(Vec3(0,0,M_PI/2.), Vec3(-0.06, 0., 0)));


  link_[link_idx_map_.find("R_FOOT")->second]->AddCollision(collision_[0]);
  link_[link_idx_map_.find("R_FOOT")->second]->AddCollision(collision_[1]);
  link_[link_idx_map_.find("L_FOOT")->second]->AddCollision(collision_[2]);
  link_[link_idx_map_.find("L_FOOT")->second]->AddCollision(collision_[3]);

  double fric(0.8);
  link_[link_idx_map_.find("R_FOOT")->second]->SetFriction(fric);
  link_[link_idx_map_.find("L_FOOT")->second]->SetFriction(fric);

  double damp(0.11);
  link_[link_idx_map_.find("R_FOOT")->second]->SetDamping(damp);
  link_[link_idx_map_.find("L_FOOT")->second]->SetDamping(damp);

  double restit(0.0);
  link_[link_idx_map_.find("R_FOOT")->second]->SetRestitution(restit);
  link_[link_idx_map_.find("L_FOOT")->second]->SetRestitution(restit);
}

void TELLO::_SetInitialConf(){
  //_setTELLO_InitialConfig();
  _setHumanoid_InitialConfig();
  KIN_UpdateFrame_All_The_Entity();
}

void TELLO::_setTELLO_InitialConfig(){
  // Case 1
  //vp_joint_[0]->m_State.m_rValue[0] = 0.0;
  //vp_joint_[1]->m_State.m_rValue[0] = 0.0;
  //vp_joint_[2]->m_State.m_rValue[0] = 0.67;// + 0.3;
  //vr_joint_[0]->m_State.m_rValue[0] = 0.0;
  //vr_joint_[1]->m_State.m_rValue[0] = 0.0;
  //vr_joint_[2]->m_State.m_rValue[0] = 0.0;

  //r_joint_[r_joint_idx_map_.find("r_hip_pitch" )->second]->m_State.m_rValue[0] = -0.3;
  //r_joint_[r_joint_idx_map_.find("r_knee")->second]->m_State.m_rValue[0] = 0.8;
  //r_joint_[r_joint_idx_map_.find("r_ankle")->second]->m_State.m_rValue[0] = -0.5;

  //r_joint_[r_joint_idx_map_.find("l_hip_pitch" )->second]->m_State.m_rValue[0] = -0.3;
  //r_joint_[r_joint_idx_map_.find("l_knee")->second]->m_State.m_rValue[0] = 0.8;
  //r_joint_[r_joint_idx_map_.find("l_ankle")->second]->m_State.m_rValue[0] = -0.5;


  // Case 2
  vp_joint_[0]->m_State.m_rValue[0] = 0.012295;
  vp_joint_[2]->m_State.m_rValue[0] = 0.644029 + 0.015;
  r_joint_[r_joint_idx_map_.find("r_hip_pitch" )->second]->m_State.m_rValue[0] = -0.418;
  r_joint_[r_joint_idx_map_.find("r_knee")->second]->m_State.m_rValue[0] = 0.936;
  r_joint_[r_joint_idx_map_.find("r_ankle")->second]->m_State.m_rValue[0] = -0.516;

  r_joint_[r_joint_idx_map_.find("l_hip_pitch" )->second]->m_State.m_rValue[0] = -0.418;
  r_joint_[r_joint_idx_map_.find("l_knee")->second]->m_State.m_rValue[0] = 0.936;
  r_joint_[r_joint_idx_map_.find("l_ankle")->second]->m_State.m_rValue[0] = -0.516;
}

void TELLO::_setHumanoid_InitialConfig(){
  vp_joint_[0]->m_State.m_rValue[0] =  0.0;
  vp_joint_[1]->m_State.m_rValue[0] = 0.0;
  vp_joint_[2]->m_State.m_rValue[0] =  0.57;
  vr_joint_[0]->m_State.m_rValue[0] = 0.0;
  vr_joint_[1]->m_State.m_rValue[0] = 0.0;
  vr_joint_[2]->m_State.m_rValue[0] = 0.0;

  // Leg
  r_joint_[r_joint_idx_map_.find("R_HipRx_to_R_Thigh" )->second]->
    m_State.m_rValue[0] = -0.3;
  r_joint_[r_joint_idx_map_.find("R_Knee")->second]->m_State.m_rValue[0] = 0.8;
  r_joint_[r_joint_idx_map_.find("R_Ankle")->second]->m_State.m_rValue[0] = -0.5;

  r_joint_[r_joint_idx_map_.find("L_HipRx_to_L_Thigh" )->second]->
    m_State.m_rValue[0] = -0.3;
  r_joint_[r_joint_idx_map_.find("L_Knee")->second]->m_State.m_rValue[0] = 0.8;
  r_joint_[r_joint_idx_map_.find("L_Ankle")->second]->m_State.m_rValue[0] = -0.5;

  // Arm
  //r_joint_[r_joint_idx_map_.find("torso_to_R_ShoulderRx" )->second]->
    //m_State.m_rValue[0] = -0.4;
  //r_joint_[r_joint_idx_map_.find("R_ShoulderRx_to_R_UpperArm")->second]->
    //m_State.m_rValue[0] = -0.1;
  //r_joint_[r_joint_idx_map_.find("R_UpperArm_to_R_ForeArm")->second]->
    //m_State.m_rValue[0] = -0.9;

  //r_joint_[r_joint_idx_map_.find("torso_to_L_ShoulderRx" )->second]->
    //m_State.m_rValue[0] = 0.4;
  //r_joint_[r_joint_idx_map_.find("L_ShoulderRx_to_L_UpperArm")->second]->
    //m_State.m_rValue[0] = 0.4;
  //r_joint_[r_joint_idx_map_.find("L_UpperArm_to_L_ForeArm")->second]->
    //m_State.m_rValue[0] = -1.1;
}