///////////////////////////////////////////////////////////////////////////////
//
//	This file defines the definitions of the repeated capabilities supported by
//	the driver.
//
//	Each entry in the map is of the following form:
//	
//	REPCAP_ENTRY(<repcap name>, <physical identifiers>, <repcap style>, <use qualified physical names>)
//
//	For example:
//
//	REPCAP_ENTRY(Channel, "C1,C2,C3", RepCapStyle::Parameter, false)
//	
//	The <physical identifiers> parameter can be a comma-separated list of physical
//	identifiers and ranges of identifiers (e.g. "C1-C3").  The list may will also
//	include nested physical names if the associated repeated capability is a 
//	child repeated capability of another repeated capability.  These nested repeated
//	capabilities are defined using the REPCAP_ENTRY_EX macro, as follows:

//	REPCAP_ENTRY_EX(<repcap name>, <physical identifiers>, <repcap style>, <use qualified physical names>, <parent repcap name>)
//
//	For example:
//
//	REPCAP_ENTRY_EX(Channel, "T1:C1-C3,T2:[C5,C6]", RepCapStyle::Parameter, false, Trace)
//
//	The syntax for repeated capability identifers is defined in IVI 3.1 Section 4.4.7.
//
#pragma once

using namespace nrt;

BEGIN_REPCAP_MAP()
	REPCAP_ENTRY(Module, "M9336A", RepCapStyle::Parameter, false)
	REPCAP_ENTRY(Resource, "Resource1", RepCapStyle::Parameter, false)
	REPCAP_ENTRY(PeerToPeerPort, "Port1", RepCapStyle::Selector, false)
	REPCAP_ENTRY(Channel, "Channel1", RepCapStyle::Parameter, false)
	REPCAP_ENTRY(DataMarker, "DataMarker1,DataMarker2,DataMarker3,DataMarker4", RepCapStyle::Parameter, false)
	REPCAP_ENTRY(SparseMarker, "SparseMarker1,SparseMarker2,SparseMarker3,SparseMarker4", RepCapStyle::Parameter, false)
	REPCAP_ENTRY(SequenceTrigger, "DefaultSequenceTriggerRns13970", RepCapStyle::Parameter, false)
	REPCAP_ENTRY(Marker, "DefaultMarkerRns13970", RepCapStyle::Parameter, false)
	REPCAP_ENTRY(External, "External1,External2", RepCapStyle::Parameter, false)
	REPCAP_ENTRY(TriggerBusLine, "PXI_TRIG0", RepCapStyle::Parameter, false)
	REPCAP_ENTRY_EX(MemoryBlock, "[Resource1]:[MemoryPC]", RepCapStyle::Parameter, false, Resource)
	REPCAP_ENTRY_EX(Peripheral, "[Resource1]:[Peripheral1]", RepCapStyle::Parameter, false, Resource)
	REPCAP_ENTRY_EX(RawTrigger, "[Resource1]:[RawTriggers1]", RepCapStyle::Parameter, false, Resource)
	REPCAP_ENTRY_EX(Board, "[Resource1]:[Board1]", RepCapStyle::Parameter, false, Resource)
	REPCAP_ENTRY_EX(AssetChannel, "", RepCapStyle::Parameter, false, Resource)
	REPCAP_ENTRY_EX(Fpga, "[Resource1]:[Board1]:[Fpga1]", RepCapStyle::Parameter, false, Board)
END_REPCAP_MAP()
